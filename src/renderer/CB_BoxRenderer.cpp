#include "renderer/CB_BoxRenderer.h"

CB_BoxRenderer::CB_BoxRenderer()
{
    //ctor
}

CB_BoxRenderer::~CB_BoxRenderer()
{
    //dtor
}

void CB_BoxRenderer::render(CB_RenderDataRel _data)
{
    CB_Texture * tex;

    CB_BoxRendererData data = *((CB_BoxRendererData*)_data.userdata);
    double tileSize = _data.tileSize;
    double tileScale = CB_Renderer::getScale(tileSize);
    if(!_data.sharedUserdata)
    {
        delete (CB_BoxRendererData*)_data.userdata;
    }
    double hW = data.w * 0.5 * tileScale;
    double hH = data.h * 0.5 * tileScale;
    double hD = data.d * 0.5 * tileScale;
    glPushMatrix();
    glTranslated(data.x * tileScale + hW, data.y * tileScale + hH, data.z * tileScale + hD);
    CB_Vector3D v1(-hW, -hH, -hD);
    CB_Vector3D v2(hW, -hH, -hD);
    CB_Vector3D v3(-hW, hH, -hD);
    CB_Vector3D v4(hW, hH, -hD);
    CB_Vector3D v5(-hW, -hH, hD);
    CB_Vector3D v6(hW, -hH, hD);
    CB_Vector3D v7(-hW, hH, hD);
    CB_Vector3D v8(hW, hH, hD);

    CB_Vector3D v[6][4] = {
        {v2, v1, v3, v4},
        {v1, v5, v7, v3},
        {v6, v2, v4, v8},
        {v7, v8, v4, v3},
        {v6, v5, v1, v2},
        {v5, v6, v8, v7},
    };

    GLdouble red = (double)((data.color >> 16) & 0xFF) / 255.0;
    GLdouble green = (double)((data.color >> 8) & 0xFF) / 255.0;
    GLdouble blue = (double)(data.color & 0xFF) / 255.0;
    GLdouble alpha = (double)((data.color >> 24) & 0xFF) / 255.0;

    glColor4d(red, green, blue, alpha);

    bool isTex2D = glIsEnabled(GL_TEXTURE_2D);

    for(int i = 0; i < 6; i++)
    {
        if(data.sheet == 0)
        {
            glDisable(GL_TEXTURE_2D);
            CB_Renderer::drawQuad(v[i][0], v[i][1], v[i][2], v[i][3], data.vertexNormals);
            if(isTex2D)
            {
                glEnable(GL_TEXTURE_2D);
            }
            continue;
        }
        //printf("%s %f,%f,%f\n", data.sides[i].c_str(), hW, hH, hD);
        CB_SpriteFrame * frame = data.sheet->getFrame(data.sides[i]);
        glEnable(GL_TEXTURE_2D);
        tex = data.sheet->getTexture(frame->texture);
        tex->bind();
        CB_Vector2D uv1((double)frame->x / tex->getWidth(), (double)frame->y / tex->getHeight());
        CB_Vector2D uv2(((double)frame->x + (double)frame->width) / tex->getWidth(), ((double)frame->y + (double)frame->height) / tex->getHeight());
        CB_Renderer::drawQuad(v[i][0], v[i][1], v[i][2], v[i][3], uv1, uv2, data.vertexNormals);
        if(!isTex2D)
        {
            glDisable(GL_TEXTURE_2D);
        }
    }
    glPopMatrix();
}

void CB_BoxRenderer::renderShader(CB_RenderDataRel data)
{
    render(data);
}

CB_RenderDataRel CB_BoxRenderer::prerender(CB_RenderDataRel _data)
{
    CB_RenderDataRel dataRel = _data;
    CB_PrerenderData * preData = new CB_PrerenderData();
    dataRel.userdata = preData;
    dataRel.renderer = CB_Renderer::getRenderer("prerender");
    dataRel.sharedUserdata = _data.sharedUserdata;

    CB_Texture * tex;

    CB_BoxRendererData data = *((CB_BoxRendererData*)_data.userdata);
    double tileSize = _data.tileSize;
    double tileScale = CB_Renderer::getScale(tileSize);
    if(!_data.sharedUserdata)
    {
        delete (CB_BoxRendererData*)_data.userdata;
    }
    double hW = data.w * 0.5 * tileScale;
    double hH = data.h * 0.5 * tileScale;
    double hD = data.d * 0.5 * tileScale;
    preData->translation = CB_Vector3D(data.x * tileScale + hW, data.y * tileScale + hH, data.z * tileScale + hD);

    CB_Vector3D v1(-hW, -hH, -hD);
    CB_Vector3D v2(hW, -hH, -hD);
    CB_Vector3D v3(-hW, hH, -hD);
    CB_Vector3D v4(hW, hH, -hD);
    CB_Vector3D v5(-hW, -hH, hD);
    CB_Vector3D v6(hW, -hH, hD);
    CB_Vector3D v7(-hW, hH, hD);
    CB_Vector3D v8(hW, hH, hD);

    CB_Vector3D v[6][4] = {
        {v2, v1, v3, v4},
        {v1, v5, v7, v3},
        {v6, v2, v4, v8},
        {v7, v8, v4, v3},
        {v6, v5, v1, v2},
        {v5, v6, v8, v7},
    };

    preData->glSettings[GL_TEXTURE_2D] = (data.sheet != 0);

    CB_Vector2D uv1(0, 0);
    CB_Vector2D uv2(0, 0);

    map<CB_Texture*,CB_ModelObject*> modelMap;
    vector<CB_Texture*> texList;

    for(int i = 0; i < 6; i++)
    {
        if(data.sheet != 0)
        {
            CB_SpriteFrame * frame = data.sheet->getFrame(data.sides[i]);
            tex = data.sheet->getTexture(frame->texture);
            uv1 = CB_Vector2D((double)frame->x / tex->getWidth(), (double)frame->y / tex->getHeight());
            uv2 = CB_Vector2D(((double)frame->x + (double)frame->width) / tex->getWidth(), ((double)frame->y + (double)frame->height) / tex->getHeight());

        }
        CB_Face face = CB_Face(CB_Renderer::createQuad(v[i][0], v[i][1], v[i][2], v[i][3], uv1, uv2, data.vertexNormals));

        if(data.sheet != 0)
        {
            face.setTexture(tex);
        }
        face.setColor(data.color);
        if(modelMap.count(tex) == 0)
        {
            modelMap[tex] = new CB_ModelObject();
            modelMap[tex]->setTexture(tex);
            texList.push_back(tex);
        }

        modelMap[tex]->addFace(face);
    }

    vector<CB_Texture*>::iterator texIt;
    for(texIt = texList.begin(); texIt < texList.end(); texIt++)
    {
        tex = *texIt;
        modelMap[tex]->preset();
        preData->models.push_back(modelMap[tex]);
    }

    return dataRel;
}

void CB_BoxRenderer::addBox(double xOrig, double yOrig, double zOrig, double x, double y, double z, double w, double h, double d, CB_SpriteSheet * sheet, string * sides, bool vertexNormals)
{
    addBox(xOrig, yOrig, zOrig, x, y, z, w, h, d, sheet, sides, 0xFFFFFFFF, vertexNormals);
}

void CB_BoxRenderer::addBox(double xOrig, double yOrig, double zOrig, double x, double y, double z, double w, double h, double d, uint32_t color, bool vertexNormals)
{
    addBox(xOrig, yOrig, zOrig, x, y, z, w, h, d, 0, 0, color, vertexNormals);
}

void CB_BoxRenderer::addBox(double xOrig, double yOrig, double zOrig, double x, double y, double z, double w, double h, double d, CB_SpriteSheet * sheet, string * sides, uint32_t color, bool vertexNormals)
{
    CB_RenderDataRel data = getBox(xOrig, yOrig, zOrig, x, y, z, w, h, d, sheet, sides, color, vertexNormals);
    double xMax = xOrig + max(abs(x), abs(x + w));
    double yMax = yOrig + max(abs(y), abs(y + d));
    double zMax = zOrig + max(abs(z), abs(z + d));
    data.drawRadius = sqrt(xMax * xMax + yMax * yMax + zMax * zMax);
    CB_Renderer::listRender(data);
}

CB_RenderDataRel CB_BoxRenderer::getBox(double xOrig, double yOrig, double zOrig, double x, double y, double z, double w, double h, double d, CB_SpriteSheet * sheet, string * sides, bool vertexNormals)
{
    return getBox(xOrig, yOrig, zOrig, x, y, z, w, h, d, sheet, sides, 0xFFFFFFFF, vertexNormals);
}

CB_RenderDataRel CB_BoxRenderer::getBox(double xOrig, double yOrig, double zOrig, double x, double y, double z, double w, double h, double d, uint32_t color, bool vertexNormals)
{
    return getBox(xOrig, yOrig, zOrig, x, y, z, w, h, d, 0, 0, color, vertexNormals);
}

CB_RenderDataRel CB_BoxRenderer::getBox(double xOrig, double yOrig, double zOrig, double x, double y, double z, double w, double h, double d, CB_SpriteSheet * sheet, string * sides, uint32_t color, bool vertexNormals)
{
    CB_BoxRendererData * data = new CB_BoxRendererData();
    data->x = x;
    data->y = y;
    data->z = z;
    data->w = w;
    data->h = h;
    data->d = d;
    data->sheet = sheet;
    for(int idx = 0; idx < 6; idx++)
    {
        if(sides == 0)
        {
            data->sides[idx] = "";
            continue;
        }
        data->sides[idx] = sides[idx];
    }
    data->color = color;
    data->vertexNormals = vertexNormals;
    CB_RenderDataRel dataRel = CB_Renderer::getRenderData(this, data, CB_Screen::getTileSize(), CB_Vector3D(xOrig, yOrig, zOrig));
    double xMax = max(abs(x), abs(x + w));
    double yMax = max(abs(y), abs(y + d));
    double zMax = max(abs(z), abs(z + d));
    dataRel.drawRadius = sqrt(xMax * xMax + yMax * yMax + zMax * zMax);
    return dataRel;
}
