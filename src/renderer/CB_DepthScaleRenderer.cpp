#include "renderer/CB_DepthScaleRenderer.h"

CB_DepthScaleRenderer::CB_DepthScaleRenderer()
{
    //ctor
}

CB_DepthScaleRenderer::~CB_DepthScaleRenderer()
{
    //dtor
}

void CB_DepthScaleRenderer::render(CB_RenderDataRel _data)
{
    CB_DepthScaleRendererData data = *((CB_DepthScaleRendererData*) _data.userdata);
    CB_RenderDataRel childData = data.childData;
    if(!_data.sharedUserdata)
    {
        delete((CB_DepthScaleRendererData*) _data.userdata);
    }
    else
    {
        childData.sharedUserdata = true;
    }
    double tileScale = CB_Renderer::getScale(_data.tileSize);
    childData.tileSize *= tileScale;
    CB_Vector3D position = childData.position * tileScale;
    position.z+= _data.position.z;
    double baseZ = CB_Screen::getZ();
    double bScale = baseZ / (baseZ - position.z);
    if(data.orthoIsBase)
    {
        childData.tileSize*= bScale;
    }
    double origOrthoZoom = CB_Screen::getOrthoZoom();
    glPushMatrix();
    CB_Screen::setOrthoZoom(origOrthoZoom / bScale);
    CB_Screen::setProjection(CB_Screen::getInterpolation());
    glMatrixMode(GL_MODELVIEW);
    glTranslated(position.x, position.y, position.z - _data.position.z);
    childData.renderer->render(childData);
    CB_Screen::setOrthoZoom(origOrthoZoom);
    CB_Screen::setProjection(CB_Screen::getInterpolation());
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void CB_DepthScaleRenderer::renderShader(CB_RenderDataRel _data)
{
    CB_DepthScaleRendererData data = *((CB_DepthScaleRendererData*) _data.userdata);
    CB_RenderDataRel childData = data.childData;
    if(!_data.sharedUserdata)
    {
        delete((CB_DepthScaleRendererData*) _data.userdata);
    }
    else
    {
        childData.sharedUserdata = true;
    }
    double tileScale = CB_Renderer::getScale(_data.tileSize);
    childData.tileSize *= tileScale;
    CB_Vector3D position = childData.position * tileScale;
    double baseZ = CB_Screen::getZ();
    double bScale = baseZ / (baseZ - position.z + _data.position.z);
    if(data.orthoIsBase)
    {
        childData.tileSize*= bScale;
        position.z*= bScale;
    }
    double origOrthoZoom = CB_Screen::getOrthoZoom();
    glPushMatrix();
    CB_Screen::setOrthoZoom(origOrthoZoom / bScale);
    CB_Screen::setProjection(CB_Screen::getInterpolation());
    glMatrixMode(GL_MODELVIEW);
    glTranslated(position.x, position.y, position.z);
    childData.renderer->render(childData);
    CB_Screen::setOrthoZoom(origOrthoZoom);
    CB_Screen::setProjection(CB_Screen::getInterpolation());
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

CB_RenderDataRel CB_DepthScaleRenderer::getDepthScaleRenderData(double x, double y, double z, CB_RenderDataRel childData)
{
    return getDepthScaleRenderData(x, y, z, childData, true);
}

CB_RenderDataRel CB_DepthScaleRenderer::getDepthScaleRenderData(double x, double y, double z, CB_RenderDataRel childData, bool orthoIsBase)
{
    CB_DepthScaleRendererData * data = new CB_DepthScaleRendererData();
    data->childData = childData;
    data->orthoIsBase = orthoIsBase;
    CB_RenderDataRel dataRel = CB_Renderer::getRenderData(this, data, CB_Screen::getTileSize(), CB_Vector3D(x, y, z));
    return dataRel;
}
