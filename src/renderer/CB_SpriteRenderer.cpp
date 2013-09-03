#include "renderer/CB_SpriteRenderer.h"

CB_SpriteRenderer::CB_SpriteRenderer()
{
    //ctor
}

CB_SpriteRenderer::~CB_SpriteRenderer()
{
    //dtor
}

void CB_SpriteRenderer::render(CB_RenderDataRel _data)
{
    CB_Texture * tex;

    CB_SpriteRendererData data = *((CB_SpriteRendererData*)_data.userdata);
    double tileSize = _data.tileSize;
    if(!_data.sharedUserdata)
    {
        delete (CB_SpriteRendererData*)_data.userdata;
    }
    glPushMatrix();
    glRotated(data.pitch, 1.0, 0.0, 0.0);
    glRotated(data.yaw, 0.0, 1.0, 0.0);
    glRotated(data.roll, 0.0, 0.0, 1.0);

    glColor4d(1.0, 1.0, 1.0, 1.0);

    bool isTex2D = glIsEnabled(GL_TEXTURE_2D);
    bool isAlphaTest = glIsEnabled(GL_ALPHA_TEST);
    bool isBackfaceCull = glIsEnabled(GL_CULL_FACE);
    int alphaFuncInt;
    GLclampf alphaFuncVal;

    glGetIntegerv(GL_ALPHA_TEST_FUNC, &alphaFuncInt);
    glGetFloatv(GL_ALPHA_TEST_REF, &alphaFuncVal);

    GLenum alphaFunc = alphaFuncInt;

    CB_SpriteFrame * frame = data.sheet->getFrame(data.sprite);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_CULL_FACE);
    glAlphaFunc(GL_GREATER, 0);
    tex = data.sheet->getTexture(frame->texture);
    tex->bind();
    CB_Vector2D uv1((double)frame->x / tex->getWidth(), (double)frame->y / tex->getHeight());
    CB_Vector2D uv2(((double)frame->x + (double)frame->width) / tex->getWidth(), ((double)frame->y + (double)frame->height) / tex->getHeight());

    if(data.mirrored)
    {
        double nX = uv2.x;
        uv2.x = uv1.x;
        uv1.x = nX;
    }

    CB_Vector2D uv3(uv2.x, uv1.y);
    CB_Vector2D uv4(uv1.x, uv2.y);

    CB_Vector3D v1(-(double)frame->xOrig, (double)frame->yOrig - (double)frame->height, 0);
    CB_Vector3D v2((double)frame->width - (double)frame->xOrig, (double)frame->yOrig - (double)frame->height, 0);
    CB_Vector3D v3((double)frame->width - (double)frame->xOrig, (double)frame->yOrig, 0);
    CB_Vector3D v4(-(double)frame->xOrig, (double)frame->yOrig, 0);

    double tileScale = CB_Renderer::getScale(tileSize);

    CB_Renderer::drawQuad(v1 * tileScale, v2 * tileScale, v3 * tileScale, v4 * tileScale, uv1, uv2, false);
    CB_Renderer::drawQuad(v2 * tileScale, v1 * tileScale, v4 * tileScale, v3 * tileScale, uv3, uv4, false);
    glAlphaFunc(alphaFunc, alphaFuncVal);
    if(!isTex2D)
    {
        glDisable(GL_TEXTURE_2D);
    }
    if(!isAlphaTest)
    {
        glDisable(GL_ALPHA_TEST);
    }
    if(!isBackfaceCull)
    {
        glDisable(GL_CULL_FACE);
    }
    glPopMatrix();
}

void CB_SpriteRenderer::renderShader(CB_RenderDataRel data)
{
    render(data);
}

void CB_SpriteRenderer::addSprite(double x, double y, double z, double pitch, double yaw, double roll, CB_SpriteSheet * sheet, string sprite)
{
    addSprite(x, y, z, pitch, yaw, roll, sheet, sprite, false);
}

void CB_SpriteRenderer::addSprite(double x, double y, double z, double pitch, double yaw, double roll, CB_SpriteSheet * sheet, string sprite, bool mirrored)
{
    CB_RenderDataRel data = getSprite(x, y, z, pitch, yaw, roll, sheet, sprite, mirrored);
    CB_Renderer::listRender(data);
}

CB_RenderDataRel CB_SpriteRenderer::getSprite(double x, double y, double z, double pitch, double yaw, double roll, CB_SpriteSheet * sheet, string sprite)
{
    return getSprite(x, y, z, pitch, yaw, roll, sheet, sprite, false);
}

CB_RenderDataRel CB_SpriteRenderer::getSprite(double x, double y, double z, double pitch, double yaw, double roll, CB_SpriteSheet * sheet, string sprite, bool mirrored)
{
    CB_SpriteRendererData * data = new CB_SpriteRendererData();
    data->pitch = pitch;
    data->yaw = yaw;
    data->roll = roll;
    data->sheet = sheet;
    data->sprite = sprite;
    data->mirrored = mirrored;
    CB_RenderDataRel dataRel = CB_Renderer::getRenderData(this, data, CB_Screen::getTileSize(), CB_Vector3D(x, y, z));
    CB_SpriteFrame * frame = sheet->getFrame(sprite);
    double xMax = max(abs((double)frame->xOrig), (double)(frame->width - frame->xOrig));
    double yMax = max(abs((double)frame->yOrig), (double)(frame->height - frame->yOrig));
    dataRel.drawRadius = sqrt(xMax * xMax + yMax * yMax);
    return dataRel;
}

void CB_SpriteRenderer::addSprite(double x, double y, double z, double pitch, double yaw, double roll, CB_SpriteSheet * sheet, string sprite, CB_RenderList * renderList)
{
    addSprite(x, y, z, pitch, yaw, roll, sheet, sprite, false, renderList);
}

void CB_SpriteRenderer::addSprite(double x, double y, double z, double pitch, double yaw, double roll, CB_SpriteSheet * sheet, string sprite, bool mirrored, CB_RenderList * renderList)
{
    CB_RenderDataRel data = getSprite(x, y, z, pitch, yaw, roll, sheet, sprite, mirrored);
    CB_Renderer::listRender(data, renderList);
}
