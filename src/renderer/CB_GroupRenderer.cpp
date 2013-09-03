#include "renderer/CB_GroupRenderer.h"

CB_GroupRenderer::CB_GroupRenderer()
{
    //ctor
}

CB_GroupRenderer::~CB_GroupRenderer()
{
    //dtor
}

void CB_GroupRenderer::render(CB_RenderDataRel _data)
{
    CB_GroupRendererData data = *((CB_GroupRendererData*) _data.userdata);
    CB_RenderList renderList = data.renderList;
    if(!_data.sharedUserdata)
    {
        delete((CB_GroupRendererData*) _data.userdata);
    }
    CB_RenderList::iterator it;
    for(it = renderList.begin(); it != renderList.end(); it++)
    {
        CB_RenderDataRel * rel = &*it;
        rel->tileSize/= CB_Renderer::getScale(_data.tileSize);
        if(_data.sharedUserdata)
        {
            rel->sharedUserdata = true;
        }
    }
    CB_Renderer::process(&renderList, _data.position.x + data.offset.x, _data.position.y + data.offset.y, _data.position.z + data.offset.z);
}

void CB_GroupRenderer::renderShader(CB_RenderDataRel data)
{
    render(data);
}

CB_RenderDataRel CB_GroupRenderer::getGroup(double x, double y, double z, double offX, double offY, double offZ, CB_RenderList renderList)
{
    CB_GroupRendererData * data = new CB_GroupRendererData();
    data->offset = CB_Vector3D(offX, offY, offZ);
    data->renderList = renderList;
    CB_RenderDataRel dataRel = CB_Renderer::getRenderData(this, data, CB_Screen::getTileSize(), CB_Vector3D(x, y, z));
    return dataRel;
}
