#include "CB_Renderer.h"
#include "renderer/CB_BoxRenderer.h"
#include "renderer/CB_SpriteRenderer.h"
#include "renderer/CB_LineRenderer.h"
#include "renderer/CB_SphereRenderer.h"
#include "renderer/CB_PrerenderRenderer.h"
#include "renderer/CB_GroupRenderer.h"
#include "renderer/CB_DepthScaleRenderer.h"

map<uint32_t,CB_Renderer*> CB_Renderer::renderMap;
map<string,uint32_t> CB_Renderer::strToRenderMap;
CB_RenderList CB_Renderer::renderDataList;
CB_RenderList CB_Renderer::renderSolidList;
SDL_mutex * CB_Renderer::sRenderMutex;

CB_Renderer::CB_Renderer()
{
    //ctor
}

CB_Renderer::~CB_Renderer()
{
    //dtor
}

CB_RenderDataRel CB_Renderer::prerender(CB_RenderDataRel data)
{
    return data;
}

bool CB_CompareRenderData(const CB_RenderDataRel& data1, const CB_RenderDataRel& data2)
{
    double dist1 = data1.renderer->getDistanceFromCamera(data1.position);
    double dist2 = data2.renderer->getDistanceFromCamera(data2.position);
    if(dist1 < dist2)
    {
        return false;
    }
    return true;
}

double CB_Renderer::getDistanceFromCamera(CB_Vector3D position)
{
    CB_Vector3D camVec = CB_Screen::getCamera()->getActualPosition();
    CB_Vector3D distVec = position - camVec;
    return distVec.length();
}

uint32_t CB_Renderer::addRenderer(string name, CB_Renderer* renderer)
{
    SDL_mutexP(sRenderMutex);
    uint32_t idx = renderMap.size();
    while(renderMap.count(idx) != 0)
    {
        idx++;
    }
    strToRenderMap[name] = idx;
    renderMap[idx] = renderer;
    SDL_mutexV(sRenderMutex);
    return idx;
}

uint32_t CB_Renderer::addRenderer(string name, uint32_t preferredIndex, CB_Renderer* renderer)
{
    SDL_mutexP(sRenderMutex);
    uint32_t idx = preferredIndex;
    while(renderMap.count(idx) != 0)
    {
        idx++;
    }
    strToRenderMap[name] = idx;
    renderMap[idx] = renderer;
    SDL_mutexV(sRenderMutex);
    return idx;
}

CB_Renderer * CB_Renderer::getRenderer(uint32_t renderID)
{
    CB_Renderer * rP = 0;
    SDL_mutexP(sRenderMutex);
    if(renderMap.count(renderID) != 0)
    {
        rP = renderMap[renderID];
    }
    SDL_mutexV(sRenderMutex);
    return rP;
}

CB_Renderer * CB_Renderer::getRenderer(string name)
{
    CB_Renderer * rP = 0;
    SDL_mutexP(sRenderMutex);
    if(strToRenderMap.count(name) != 0)
    {
        rP = getRenderer(strToRenderMap[name]);
    }
    SDL_mutexV(sRenderMutex);
    return rP;
}

CB_RenderDataRel CB_Renderer::getRenderData(uint32_t renderID, void * userdata, double tileSize, CB_Vector3D position)
{
    CB_RenderDataRel data;
    data.position = position;
    data.tileSize = tileSize;
    data.userdata = userdata;
    data.renderer = getRenderer(renderID);
    return data;
}

CB_RenderDataRel CB_Renderer::getRenderData(string name, void * userdata, double tileSize, CB_Vector3D position)
{
    CB_RenderDataRel data;
    data.position = position;
    data.tileSize = tileSize;
    data.userdata = userdata;
    data.renderer = getRenderer(name);
    return data;
}

CB_RenderDataRel CB_Renderer::getRenderData(CB_Renderer * renderer, void * userdata, double tileSize, CB_Vector3D position)
{
    CB_RenderDataRel data;
    data.position = position;
    data.tileSize = tileSize;
    data.userdata = userdata;
    data.renderer = renderer;
    return data;
}

void CB_Renderer::listRender(uint32_t renderID, void * userdata, double tileSize, CB_Vector3D position)
{
    CB_RenderDataRel data = getRenderData(renderID, userdata, tileSize, position);
    SDL_mutexP(sRenderMutex);
    renderDataList.push_back(data);
    SDL_mutexV(sRenderMutex);
}

void CB_Renderer::listRender(string name, void * userdata, double tileSize, CB_Vector3D position)
{
    CB_RenderDataRel data = getRenderData(name, userdata, tileSize, position);
    SDL_mutexP(sRenderMutex);
    renderDataList.push_back(data);
    SDL_mutexV(sRenderMutex);
}

void CB_Renderer::listRender(CB_Renderer * renderer, void * userdata, double tileSize, CB_Vector3D position)
{
    CB_RenderDataRel data = getRenderData(renderer, userdata, tileSize, position);
    SDL_mutexP(sRenderMutex);
    renderDataList.push_back(data);
    SDL_mutexV(sRenderMutex);
}

void CB_Renderer::listRender(uint32_t renderID, void * userdata, double tileSize, CB_Vector3D position, CB_RenderList * renderList)
{
    CB_RenderDataRel data;
    data.position = position;
    data.tileSize = tileSize;
    data.userdata = userdata;
    data.renderer = getRenderer(renderID);
    renderList->push_back(data);
}

void CB_Renderer::listRender(string name, void * userdata, double tileSize, CB_Vector3D position, CB_RenderList * renderList)
{
    CB_RenderDataRel data;
    data.position = position;
    data.tileSize = tileSize;
    data.userdata = userdata;
    data.renderer = getRenderer(name);
    renderList->push_back(data);
}

void CB_Renderer::listRender(CB_Renderer * renderer, void * userdata, double tileSize, CB_Vector3D position, CB_RenderList * renderList)
{
    CB_RenderDataRel data;
    data.position = position;
    data.tileSize = tileSize;
    data.userdata = userdata;
    data.renderer = renderer;
    renderList->push_back(data);
}

void CB_Renderer::listRender(CB_RenderDataRel data)
{
    listRender(data, 0, 0, 0);
}

void CB_Renderer::listRender(CB_RenderDataRel data, double x, double y, double z)
{
    data.position.x+= x;
    data.position.y+= y;
    data.position.z+= z;
    SDL_mutexP(sRenderMutex);
    if(data.blendMode == CB_BLENDMODE_SOLID)
    {
        renderSolidList.push_back(data);
    }
    else
    {
        renderDataList.push_back(data);
    }
    SDL_mutexV(sRenderMutex);
}

void CB_Renderer::listRender(CB_RenderDataRel data, CB_RenderList * renderList)
{
    listRender(data, 0, 0, 0, renderList);
}

void CB_Renderer::listRender(CB_RenderDataRel data, double x, double y, double z, CB_RenderList * renderList)
{
    data.position.x+= x;
    data.position.y+= y;
    data.position.z+= z;
    renderList->push_back(data);
}

double CB_Renderer::getScale(double tileSize)
{
    return CB_Screen::getTileSize() / tileSize;
}

void CB_Renderer::process()
{
    process(0, 0, 0);
}

void CB_Renderer::process(double x, double y, double z)
{
    SDL_mutexP(sRenderMutex);
    process(&renderDataList, &renderSolidList, x, y, z);
    SDL_mutexV(sRenderMutex);
}

void CB_Renderer::process(CB_RenderList * renderList)
{
    process(renderList, 0, 0, 0);
}

void CB_Renderer::process(CB_RenderList * renderList, double x, double y, double z)
{
    process(renderList, 0, x, y, z);
}

void CB_Renderer::process(CB_RenderList * renderList, CB_RenderList * solidList, double x, double y, double z)
{
    renderList->sort(CB_CompareRenderData);
    if(solidList != 0)
    {
        renderList->insert(renderList->begin(), solidList->begin(), solidList->end());
        solidList->clear();
    }
    double fL = CB_Screen::getZ();
    CB_Camera * cam = CB_Screen::getCamera();
    CB_Quaternion camRotInv = cam->getInverseRotation();
    CB_Vector3D camPosOrtho = cam->getPosition();
    CB_Vector3D camPosPersp = cam->getActualPosition();
    CB_Vector3D adjustedPos(x, y, z);
    double oScale = 1 / CB_Screen::getOrthoZoom();
    int blendSrc;
    int blendDst;
    glGetIntegerv(GL_BLEND_SRC, &blendSrc);
    glGetIntegerv(GL_BLEND_DST, &blendDst);
    bool isBlend = glIsEnabled(GL_BLEND);
    glEnable(GL_BLEND);
    while(!renderList->empty())
    {
        CB_RenderDataRel data = renderList->front();
        bool doDraw = false;
        if(data.drawRadius == 0)
        {
            doDraw = true;
        }
        else
        {
            CB_Vector3D posOrtho = data.position + adjustedPos;
            CB_Vector3D posPersp = data.position + adjustedPos;
            posOrtho = posOrtho - camPosOrtho;
            posPersp = posPersp - camPosPersp;
            double len = posPersp.length();
            posPersp = (camRotInv * posPersp) * len;
            double fScale = fL / (posPersp.z);
            posOrtho = posOrtho * oScale;
            posPersp = posPersp * fScale;
            double ipol = CB_Screen::getInterpolation();
            ipol = ipol * ipol * ipol;
            double xP = abs(posPersp.x) * ipol + abs(posOrtho.x) * (1.0 - ipol);
            double yP = abs(posPersp.y) * ipol + abs(posOrtho.y) * (1.0 - ipol);
            double zL = abs(fScale * data.drawRadius) * ipol + abs(oScale * data.drawRadius) * (1.0 - ipol);
            if(xP - zL <= CB_Screen::getWidth() && yP - zL <= CB_Screen::getHeight())
            {
                doDraw = true;
            }
        }
        if(doDraw)
        {
            glPushMatrix();
            switch(data.blendMode)
            {
                case CB_BLENDMODE_SOLID:
                {
                    glBlendFunc(GL_ONE, GL_ZERO);
                    break;
                }
                case CB_BLENDMODE_ALPHA:
                {
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    break;
                }
                case CB_BLENDMODE_ADDITIVE:
                {
                    glBlendFunc(GL_ONE, GL_ONE);
                    break;
                }
            }
            glTranslated(data.position.x, data.position.y, data.position.z);
            glRotated(data.rotation.x, 1.0, 0.0, 0.0);
            glRotated(data.rotation.y, 0.0, 1.0, 0.0);
            glRotated(data.rotation.z, 0.0, 0.0, 1.0);
            data.renderer->render(data);
            glPopMatrix();
        }
        renderList->pop_front();
    }
    glBlendFunc(blendSrc, blendDst);
    if(!isBlend)
    {
        glDisable(GL_BLEND);
    }
}

void CB_Renderer::drawQuad(const CB_Vector3D& vertBL, const CB_Vector3D& vertBR, const CB_Vector3D& vertTR, const CB_Vector3D& vertTL)
{
    drawQuad(vertBL, vertBR, vertTR, vertTL, false);
}

void CB_Renderer::drawQuad(const CB_Vector3D& vertBL, const CB_Vector3D& vertBR, const CB_Vector3D& vertTR, const CB_Vector3D& vertTL, bool vertNormals)
{
    drawQuad(vertBL, vertBR, vertTR, vertTL, CB_Vector2D(0, 0), CB_Vector2D(0, 0), vertNormals);
}

void CB_Renderer::drawQuad(const CB_Vector3D& vertBL, const CB_Vector3D& vertBR, const CB_Vector3D& vertTR, const CB_Vector3D& vertTL, CB_Vector2D uv1, CB_Vector2D uv2)
{
    drawQuad(vertBL, vertBR, vertTR, vertTL, uv1, uv2, false);
}

void CB_Renderer::drawQuad(const CB_Vector3D& vertBL, const CB_Vector3D& vertBR, const CB_Vector3D& vertTR, const CB_Vector3D& vertTL, CB_Vector2D uv1, CB_Vector2D uv2, bool vertNormals)
{
    if(vertNormals)
    {
        CB_Vector3D norm;
        glBegin(GL_QUADS);
        norm = vertBL;
        norm.normalize();
        glNormal3d(norm.x, norm.y, norm.z);
        glTexCoord2d(uv1.x, uv2.y);
        glVertex3d(vertBL.x, vertBL.y, vertBL.z);
        norm = vertBR;
        norm.normalize();
        glNormal3d(norm.x, norm.y, norm.z);
        glTexCoord2d(uv2.x, uv2.y);
        glVertex3d(vertBR.x, vertBR.y, vertBR.z);
        norm = vertTR;
        norm.normalize();
        glNormal3d(norm.x, norm.y, norm.z);
        glTexCoord2d(uv2.x, uv1.y);
        glVertex3d(vertTR.x, vertTR.y, vertTR.z);
        norm = vertTL;
        norm.normalize();
        glNormal3d(norm.x, norm.y, norm.z);
        glTexCoord2d(uv1.x, uv1.y);
        glVertex3d(vertTL.x, vertTL.y, vertTL.z);
        glEnd();
    }
    else
    {
        CB_Vector3D norm = vertBR;
        norm = norm - vertBL;
        CB_Vector3D tVec = vertTR;
        tVec = tVec - vertBL;
        norm = norm.crossProduct(tVec);
        norm.normalize();

        glBegin(GL_QUADS);
        glNormal3d(norm.x, norm.y, norm.z);
        glTexCoord2d(uv1.x, uv2.y);
        glVertex3d(vertBL.x, vertBL.y, vertBL.z);
        glTexCoord2d(uv2.x, uv2.y);
        glVertex3d(vertBR.x, vertBR.y, vertBR.z);
        glTexCoord2d(uv2.x, uv1.y);
        glVertex3d(vertTR.x, vertTR.y, vertTR.z);
        glTexCoord2d(uv1.x, uv1.y);
        glVertex3d(vertTL.x, vertTL.y, vertTL.z);
        glEnd();
    }
}

CB_Face CB_Renderer::createQuad(const CB_Vector3D& vertBL, const CB_Vector3D& vertBR, const CB_Vector3D& vertTR, const CB_Vector3D& vertTL, CB_Vector2D uv1, CB_Vector2D uv2, bool vertNormals)
{
    CB_Face face;
    vector<CB_Vertex> verts;
    vector<CB_Vector2D> coords;

    CB_Vector3D norm = vertBR;
    norm = norm - vertBL;
    CB_Vector3D tVec = vertTR;
    tVec = tVec - vertBL;
    norm = norm.crossProduct(tVec);
    norm.normalize();

    CB_Vertex vert;

    vert.setPosition(vertBL);
    vert.setNormal((vertNormals ? ((CB_Vector3D)vertBL).getNormalized() : norm));
    verts.push_back(vert);
    vert.setPosition(vertBR);
    vert.setNormal((vertNormals ? ((CB_Vector3D)vertBR).getNormalized() : norm));
    verts.push_back(vert);
    vert.setPosition(vertTR);
    vert.setNormal((vertNormals ? ((CB_Vector3D)vertTR).getNormalized() : norm));
    verts.push_back(vert);
    vert.setPosition(vertTL);
    vert.setNormal((vertNormals ? ((CB_Vector3D)vertTL).getNormalized() : norm));
    verts.push_back(vert);

    coords.push_back(CB_Vector2D(uv1.x, uv2.y));
    coords.push_back(CB_Vector2D(uv2.x, uv2.y));
    coords.push_back(CB_Vector2D(uv2.x, uv1.y));
    coords.push_back(CB_Vector2D(uv1.x, uv1.y));

    face.setVertices(verts);
    face.setTexCoords(coords);
    return face;
}

void CB_Renderer::init()
{
    addRenderer("line", 0, new CB_LineRenderer());
    addRenderer("sprite", 1, new CB_SpriteRenderer());
    addRenderer("box", 2, new CB_BoxRenderer());
    addRenderer("sphere", 3, new CB_SphereRenderer());
    addRenderer("prerender", 1000, new CB_PrerenderRenderer());
    addRenderer("group", 1001, new CB_GroupRenderer());
    addRenderer("depthscale", 1002, new CB_DepthScaleRenderer());
}
