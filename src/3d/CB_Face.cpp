#include "3d/CB_Face.h"

CB_Face::CB_Face()
{
    texture = 0;
    count = 0;
    vertexVBOID = 0;
    //ctor
}

CB_Face::~CB_Face()
{
    //dtor
}

void CB_Face::render()
{
    glPushMatrix();
    size_t sSize = sizeof(CB_VertexData);
    if(count == 0)
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

    switch(count)
    {
        case 1:
        {
            glDrawElements(GL_POINTS, count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
            break;
        }
        case 2:
        {
            glDrawElements(GL_LINES, count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
            break;
        }
        case 3:
        {
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
            break;
        }
        case 4:
        {
            glDrawElements(GL_QUADS, count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
            break;
        }
        default:
        {
            glDrawElements(GL_POLYGON, count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
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
}

vector<CB_VertexData> CB_Face::prerender()
{
    size_t tCount = vertices.size();
    vector<CB_VertexData> vertData;

    vector<CB_Vertex>::iterator vertIt = vertices.begin();
    vector<CB_Vector2D>::iterator texIt = texCoords.begin();

    uint8_t red = (color >> 16) & 0xFF;
    uint8_t green = (color >> 8) & 0xFF;
    uint8_t blue = color & 0xFF;
    uint8_t alpha = (color >> 24) & 0xFF;

    for(size_t i = 0; i < tCount; i++)
    {
        CB_VertexData vDat;
        CB_Vertex vert = *(vertIt + i);
        CB_Vector3D pos = vert.getPosition();
        CB_Vector3D norm = vert.getNormal();
        CB_Vector2D coord = *(texIt + i);

        vDat.posX = pos.x;
        vDat.posY = pos.y;
        vDat.posZ = pos.z;
        vDat.norX = norm.x;
        vDat.norY = norm.y;
        vDat.norZ = norm.z;
        vDat.texX = coord.x;
        vDat.texY = coord.y;
        vDat.colR = red;
        vDat.colG = green;
        vDat.colB = blue;
        vDat.colA = alpha;

        vertData.push_back(vDat);
    }
    return vertData;
}

void CB_Face::preset()
{
    preset(prerender());
}

void CB_Face::preset(vector<CB_VertexData> vertData)
{
    size_t sSize = sizeof(CB_VertexData);
    glGenBuffers(1, &vertexVBOID);
    glGenBuffers(1, &indexVBOID);
    count = vertices.size();
    CB_VertexData verts[count];
    uint16_t ind[count];

    vector<CB_VertexData>::iterator vB = vertData.begin();

    for(size_t i = 0; i < count; i++)
    {
        verts[i] = *(vB + i);

        ind[i] = (uint16_t)i;
    }
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBOID);
    glBufferData(GL_ARRAY_BUFFER, count * sSize, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, count * sSize, &verts);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint16_t), ind, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vertexVBOID);
    glNormalPointer(GL_FLOAT, sSize, BUFFER_OFFSET(12));
    if(texture)
    {
        glTexCoordPointer(2, GL_FLOAT, sSize, BUFFER_OFFSET(24));
    }
    glColorPointer(4, GL_UNSIGNED_BYTE, sSize, BUFFER_OFFSET(32));
    glVertexPointer(3, GL_FLOAT, sSize, BUFFER_OFFSET(0));
}
