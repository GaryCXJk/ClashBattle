#include "3d/CB_ModelObject.h"

CB_ModelObject::CB_ModelObject()
{
    hasPrerendered = false;
}

CB_ModelObject::~CB_ModelObject()
{
    //dtor
}

void CB_ModelObject::render()
{
    if(hasPrerendered)
    {
        glCallList(displayList);
        return;
    }
    hasPrerendered = true;
    displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE_AND_EXECUTE);
    glPushMatrix();
    size_t sSize = sizeof(CB_VertexData);
    if(indCount == 0)
    {
        preset();
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBOID);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sSize, BUFFER_OFFSET(12));
    glColorPointer(4, GL_UNSIGNED_BYTE, sSize, BUFFER_OFFSET(32));
    if(texture)
    {
        texture->bind();
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, sSize, BUFFER_OFFSET(24));
    }
    glVertexPointer(3, GL_FLOAT, sSize, BUFFER_OFFSET(0));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);

    switch(minCount)
    {
        case 1:
        {
            glDrawElements(GL_POINTS, indCount, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
            break;
        }
        case 2:
        {
            glDrawElements(GL_LINES, indCount, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
            break;
        }
        default:
        {
            glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
            break;
        }
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    if(texture)
    {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    glPopMatrix();
    glEndList();
}

void CB_ModelObject::renderShader()
{
    if(hasPrerendered)
    {
        glCallList(displayList);
        return;
    }
    hasPrerendered = true;
    displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE_AND_EXECUTE);
    glPushMatrix();
    CB_ShaderManager::useShader("basic");
    size_t sSize = sizeof(CB_VertexData);
    if(indCount == 0)
    {
        preset();
    }

    GLint a_coord3d = CB_ShaderManager::getAttribute("basic", "coord3d");
    GLint a_coord2d = CB_ShaderManager::getAttribute("basic", "coord2d");
    GLint a_color4d = CB_ShaderManager::getAttribute("basic", "color4d");

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBOID);
    glEnableVertexAttribArray(a_coord3d);
    glEnableVertexAttribArray(a_coord2d);
    glEnableVertexAttribArray(a_color4d);
    if(a_coord3d > -1)
    {
        glVertexAttribPointer(a_coord3d, 3, GL_FLOAT, GL_FALSE, sSize, 0);
    }
    if(a_coord2d > -1)
    {
        if(texture)
        {
            GLint u_texture = CB_ShaderManager::getUniform("basic", "tex_color");
            glActiveTexture(GL_TEXTURE0);
            texture->bind();
            glUniform1i(u_texture, 0);
            glVertexAttribPointer(a_coord2d, 2, GL_FLOAT, GL_FALSE, sSize, BUFFER_OFFSET(24));
        }
    }
    if(a_color4d > -1)
    {
        glVertexAttribPointer(a_color4d, 4, GL_UNSIGNED_BYTE, GL_FALSE, sSize, BUFFER_OFFSET(32));
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);

    switch(minCount)
    {
        case 1:
        {
            glDrawElements(GL_POINTS, indCount, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
            break;
        }
        case 2:
        {
            glDrawElements(GL_LINES, indCount, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
            break;
        }
        default:
        {
            glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
            break;
        }
    }
    glDisableVertexAttribArray(a_coord3d);
    glDisableVertexAttribArray(a_color4d);

    glUseProgram(0);
    glPopMatrix();
    glEndList();
}

void CB_ModelObject::addFace(CB_Face face)
{
    faces.push_back(face);
}

void CB_ModelObject::preset()
{
    size_t sSize = sizeof(CB_VertexData);
    glGenBuffers(1, &vertexVBOID);
    glGenBuffers(1, &indexVBOID);

    vector<CB_VertexData> data;
    vector<uint16_t> indices;

    uint16_t curIndex = 0;

    vector<CB_Face>::iterator fIt;
    vector<CB_VertexData>::iterator vIt;

    minCount = 3;

    for(fIt = faces.begin(); fIt < faces.end(); fIt++)
    {
        CB_Face face = *fIt;
        minCount = min(minCount, face.size());
    }

    for(fIt = faces.begin(); fIt < faces.end(); fIt++)
    {
        CB_Face face = *fIt;
        vector<CB_VertexData> subData = face.prerender();
        uint16_t firstInd = 0;
        uint16_t prevInd = 0;
        for(vIt = subData.begin(); vIt < subData.end(); vIt++)
        {
            size_t i = vIt - subData.begin();
            if(i >= minCount)
            {
                if(minCount > 2 && (i - 2) % (minCount - 2) == 0)
                {
                    indices.push_back(firstInd);
                }
                if(minCount > 2)
                {
                    indices.push_back(prevInd);
                }
            }
            vector<CB_VertexData>::iterator vsIt;

            CB_VertexData vD = *vIt;

            vsIt = find(data.begin(), data.end(), vD);

            uint16_t cId;

            if(vsIt == data.end())
            {
                data.push_back(vD);
                cId = curIndex;
                curIndex++;
            }
            else
            {
                cId = (uint16_t)(vsIt - data.begin());
            }
            indices.push_back(cId);
            if(i == 0)
            {
                firstInd = cId;
            }
            prevInd = cId;
        }
    }

    vertCount = data.size();
    indCount = indices.size();
    CB_VertexData verts[vertCount];
    uint16_t ind[indCount];

    for(size_t i = 0; i < vertCount; i++)
    {
        verts[i] = *(data.begin() + i);
    }

    for(size_t i = 0; i < indCount; i++)
    {
        ind[i] = *(indices.begin() + i);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBOID);
    glBufferData(GL_ARRAY_BUFFER, vertCount * sSize, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertCount * sSize, &verts);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indCount * sizeof(uint16_t), ind, GL_STATIC_DRAW);
}
