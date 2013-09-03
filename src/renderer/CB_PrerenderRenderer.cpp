#include "renderer/CB_PrerenderRenderer.h"

CB_PrerenderRenderer::CB_PrerenderRenderer()
{
    //ctor
}

CB_PrerenderRenderer::~CB_PrerenderRenderer()
{
    //dtor
}

void CB_PrerenderRenderer::render(CB_RenderDataRel _data)
{
    glPushMatrix();
    CB_PrerenderData data = *((CB_PrerenderData*)_data.userdata);
    if(!_data.sharedUserdata)
    {
        delete (CB_PrerenderData*)_data.userdata;
    }
    CB_Vector3D pos = data.translation;
    CB_Vector3D rot = data.rotation;

    //printf("\n%f %f %f\n", pos.x, pos.y, pos.z);

    glTranslated(pos.x, pos.y, pos.z);
    glRotated(rot.x, 1.0, 0.0, 0.0);
    glRotated(rot.y, 0.0, 1.0, 0.0);
    glRotated(rot.z, 0.0, 0.0, 1.0);

    map<GLenum, bool> curSettings;
    map<GLenum, bool>::iterator setIt;

    for(setIt = data.glSettings.begin(); setIt != data.glSettings.end(); setIt++)
    {
        curSettings[setIt->first] = glIsEnabled(setIt->first);
        if(setIt->second)
        {
            glEnable(setIt->first);
        }
        else
        {
            glDisable(setIt->first);
        }
    }
    vector<CB_Face*>::iterator fIt;
    for(fIt = data.faces.begin(); fIt < data.faces.end(); fIt++)
    {
        (*fIt)->render();
    }
    vector<CB_ModelObject*>::iterator mIt;
    for(mIt = data.models.begin(); mIt < data.models.end(); mIt++)
    {
        (*mIt)->render();
    }
    for(setIt = curSettings.begin(); setIt != curSettings.end(); setIt++)
    {
        if(setIt->second)
        {
            glEnable(setIt->first);
        }
        else
        {
            glDisable(setIt->first);
        }
    }
    glPopMatrix();
}

void CB_PrerenderRenderer::renderShader(CB_RenderDataRel _data)
{
    glPushMatrix();
    CB_PrerenderData data = *((CB_PrerenderData*)_data.userdata);
    if(!_data.sharedUserdata)
    {
        delete (CB_PrerenderData*)_data.userdata;
    }
    CB_Vector3D pos = data.translation;
    CB_Vector3D rot = data.rotation;

    //printf("\n%f %f %f\n", pos.x, pos.y, pos.z);

    glTranslated(pos.x, pos.y, pos.z);
    glRotated(rot.x, 1.0, 0.0, 0.0);
    glRotated(rot.y, 0.0, 1.0, 0.0);
    glRotated(rot.z, 0.0, 0.0, 1.0);

    map<GLenum, bool> curSettings;
    map<GLenum, bool>::iterator setIt;

    for(setIt = data.glSettings.begin(); setIt != data.glSettings.end(); setIt++)
    {
        curSettings[setIt->first] = glIsEnabled(setIt->first);
        if(setIt->second)
        {
            glEnable(setIt->first);
        }
        else
        {
            glDisable(setIt->first);
        }
    }
    vector<CB_Face*>::iterator fIt;
    for(fIt = data.faces.begin(); fIt < data.faces.end(); fIt++)
    {
        (*fIt)->render();
    }
    vector<CB_ModelObject*>::iterator mIt;
    for(mIt = data.models.begin(); mIt < data.models.end(); mIt++)
    {
        (*mIt)->renderShader();
    }
    for(setIt = curSettings.begin(); setIt != curSettings.end(); setIt++)
    {
        if(setIt->second)
        {
            glEnable(setIt->first);
        }
        else
        {
            glDisable(setIt->first);
        }
    }
    glPopMatrix();
}
