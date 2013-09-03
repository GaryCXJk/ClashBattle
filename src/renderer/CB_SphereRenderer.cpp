#include "renderer/CB_SphereRenderer.h"

CB_SphereRenderer::CB_SphereRenderer()
{
    //ctor
}

CB_SphereRenderer::~CB_SphereRenderer()
{
    //dtor
}

void CB_SphereRenderer::render(CB_RenderDataRel _data)
{
    //CB_Texture * tex;

    CB_SphereRendererData data = *((CB_SphereRendererData*)_data.userdata);
    double tileScale = CB_Renderer::getScale(_data.tileSize);
    if(!_data.sharedUserdata)
    {
        delete (CB_SphereRendererData*)_data.userdata;
    }
    double radius = data.radius * tileScale;
    uint16_t slices = data.slices;
    uint16_t stacks = data.stacks;

    if(slices < 4)
    {
        slices = 4;
    }
    if(stacks < 2)
    {
        stacks = 2;
    }

    GLdouble red = (double)((data.color >> 16) & 0xFF) / 255.0;
    GLdouble green = (double)((data.color >> 8) & 0xFF) / 255.0;
    GLdouble blue = (double)(data.color & 0xFF) / 255.0;
    GLdouble alpha = (double)((data.color >> 24) & 0xFF) / 255.0;

    glColor4d(red, green, blue, alpha);
    bool isTex2D = glIsEnabled(GL_TEXTURE_2D);

    if(data.sheet == 0)
    {
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        glEnable(GL_TEXTURE_2D);
    }

    CB_Vector3D vertices[slices * stacks + 2];

    printf("Slices: %d - Stacks: %d\n", slices, stacks);
    vertices[0] = CB_Vector3D(0, radius, 0);
    for(uint16_t stack = 0; stack < stacks; stack++)
    {
        for(uint16_t slice = 0; slice < slices; slice++)
        {
            printf("%d %d\n", slice, stack);
            double yWidth = cos(-PI / 2 + (PI / (double)(stacks + 1)) * (double)(stack + 1));
            double yHeight = -sin(-PI / 2 + (PI / (double)(stacks + 1)) * (double)(stack + 1));
            double xSize = sin((PI / (double)slices) * slice * 2.0 + PI) * yWidth;
            double zSize = -cos((PI / (double)slices) * slice * 2.0 + PI) * yWidth;

            vertices[slice + stack * slices + 1] = CB_Vector3D(xSize * radius, yHeight * radius, zSize * radius);

            if(slice > 0)
            {
                printf("Creating from %d %d\n", slice, stack);
                CB_Vector3D v0 = vertices[slice + (stack - 1) * slices];
                CB_Vector3D v1 = vertices[slice + (stack - 1) * slices + 1];
                CB_Vector3D v2 = vertices[slice + stack * slices + 1];
                CB_Vector3D v3 = vertices[slice + stack * slices];
                if(stack == 0)
                {
                    v0 = vertices[0];
                    v1 = vertices[0];
                }
                if(data.sheet == 0)
                {
                    CB_Renderer::drawQuad(v0, v1, v2, v3, data.vertexNormals);
                }
            }
        }
        CB_Vector3D v0 = vertices[(stack - 1) * slices];
        CB_Vector3D v1 = vertices[(stack - 1) * slices + 1];
        CB_Vector3D v2 = vertices[stack * slices + 1];
        CB_Vector3D v3 = vertices[stack * slices];
        if(stack == 0)
        {
            v0 = vertices[0];
            v1 = vertices[0];
        }
        if(data.sheet == 0)
        {
            CB_Renderer::drawQuad(v0, v1, v2, v3, data.vertexNormals);
        }
    }

    uint16_t vSize = slices * stacks + 1;
    vertices[vSize] = CB_Vector3D(0, -data.radius, 0);

    for(uint16_t slice = 0; slice < slices; slice++)
    {
        CB_Vector3D v0 = vertices[vSize - slices + slice];
        CB_Vector3D v1 = vertices[vSize - slices + ((slice + 1) % slices)];
        CB_Vector3D v2 = vertices[vSize];
        CB_Vector3D v3 = vertices[vSize];

        if(data.sheet == 0)
        {
            CB_Renderer::drawQuad(v0, v1, v2, v3, data.vertexNormals);
        }
    }

    if(data.sheet == 0 && isTex2D)
    {
        glEnable(GL_TEXTURE_2D);
    }
    if(data.sheet != 0 && !isTex2D)
    {
        glDisable(GL_TEXTURE_2D);
    }
}

void CB_SphereRenderer::renderShader(CB_RenderDataRel _data)
{
    render(_data);
}

void CB_SphereRenderer::addSphere(double x, double y, double z, double radius, uint16_t slices, uint16_t stacks, CB_SpriteSheet * sheet, vector<string> sides, bool vertexNormals)
{
    addSphere(x, y, z, radius, slices, stacks, sheet, sides, 0xFFFFFFFF, vertexNormals);
}

void CB_SphereRenderer::addSphere(double x, double y, double z, double radius, uint16_t slices, uint16_t stacks, uint32_t color, bool vertexNormals)
{
    vector<string> eVec;
    addSphere(x, y, z, radius, slices, stacks, 0, eVec, color, vertexNormals);
}

void CB_SphereRenderer::addSphere(double x, double y, double z, double radius, uint16_t slices, uint16_t stacks, CB_SpriteSheet * sheet, vector<string> sides, uint32_t color, bool vertexNormals)
{
    CB_RenderDataRel data = getSphere(x, y, z, radius, slices, stacks, sheet, sides, color, vertexNormals);
    CB_Renderer::listRender(data);
}

CB_RenderDataRel CB_SphereRenderer::getSphere(double x, double y, double z, double radius, uint16_t slices, uint16_t stacks, CB_SpriteSheet * sheet, vector<string> sides, uint32_t color, bool vertexNormals)
{
    CB_SphereRendererData * data = new CB_SphereRendererData();
    data->radius = radius;
    data->slices = slices;
    data->stacks = stacks;
    data->sheet = sheet;
    data->sides = sides;
    data->color = color;
    data->vertexNormals = vertexNormals;
    CB_RenderDataRel dataRel = CB_Renderer::getRenderData(this, data, CB_Screen::getTileSize(), CB_Vector3D(x, y, z));
    dataRel.drawRadius = radius;
    return dataRel;
}
