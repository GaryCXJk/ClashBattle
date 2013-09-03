#ifndef CB_RENDERER_H
#define CB_RENDERER_H
#include "ClashBattle.h"
#include "CB_Screen.h"
#include "CB_Camera.h"
#include "CB_SpriteSheet.h"
#include "CB_ShaderManager.h"
#include "util/CB_Vector2D.h"
#include "util/CB_Vector3D.h"
#include "3d/CB_Vertex.h"
#include "3d/CB_Face.h"
#include "3d/CB_ModelObject.h"

class CB_Renderer;

enum CB_BlendMode
{
    CB_BLENDMODE_SOLID = 0,
    CB_BLENDMODE_ALPHA = 1,
    CB_BLENDMODE_ADDITIVE = 2
};

struct CB_RenderDataRel
{
    CB_Vector3D position;
    CB_Vector3D rotation;
    double drawRadius;
    double tileSize;
    CB_Renderer * renderer;
    void * userdata;
    bool sharedUserdata;
    CB_BlendMode blendMode;
    CB_RenderDataRel()
    {
        drawRadius = 0;
        renderer = 0;
        userdata = 0;
        sharedUserdata = false;
        blendMode = CB_BLENDMODE_SOLID;
    }
};

struct CB_PrerenderData
{
    vector<CB_Face*> faces;
    vector<CB_ModelObject*> models;
    CB_Vector3D translation;
    CB_Vector3D rotation;
    map<GLenum, bool> glSettings;
    map<GLenum, int> intParam;
    map<GLenum, float> floatParam;
};

typedef list<CB_RenderDataRel> CB_RenderList;

class CB_Renderer
{
    public:
        CB_Renderer();
        virtual ~CB_Renderer();
        virtual void render(CB_RenderDataRel data) = 0;
        virtual void renderShader(CB_RenderDataRel data) = 0;
        //virtual GLuint getVBO(CB_RenderDataRel data) = 0;
        virtual CB_RenderDataRel prerender(CB_RenderDataRel data);

        static double getDistanceFromCamera(CB_Vector3D position);
        static uint32_t addRenderer(string name, CB_Renderer* renderer);
        static uint32_t addRenderer(string name, uint32_t preferredIndex, CB_Renderer* renderer);
        static CB_Renderer * getRenderer(uint32_t renderID);
        static CB_Renderer * getRenderer(string name);
        static CB_RenderDataRel getRenderData(uint32_t renderID, void * userdata, double tileSize, CB_Vector3D position);
        static CB_RenderDataRel getRenderData(string name, void * userdata, double tileSize, CB_Vector3D position);
        static CB_RenderDataRel getRenderData(CB_Renderer * renderer, void * userdata, double tileSize, CB_Vector3D position);
        static void listRender(uint32_t renderID, void * userdata, double tileSize, CB_Vector3D position);
        static void listRender(string name, void * userdata, double tileSize, CB_Vector3D position);
        static void listRender(CB_Renderer * renderer, void * userdata, double tileSize, CB_Vector3D position);
        static void listRender(uint32_t renderID, void * userdata, double tileSize, CB_Vector3D position, CB_RenderList * renderList);
        static void listRender(string name, void * userdata, double tileSize, CB_Vector3D position, CB_RenderList * renderList);
        static void listRender(CB_Renderer * renderer, void * userdata, double tileSize, CB_Vector3D position, CB_RenderList * renderList);
        static void listRender(CB_RenderDataRel data);
        static void listRender(CB_RenderDataRel data, double x, double y, double z);
        static void listRender(CB_RenderDataRel data, CB_RenderList * renderList);
        static void listRender(CB_RenderDataRel data, double x, double y, double z, CB_RenderList * renderList);
        static double getScale(double tileSize);
        static void process();
        static void process(double x, double y, double z);
        static void process(CB_RenderList * renderList);
        static void process(CB_RenderList * renderList, double x, double y, double z);
        static void process(CB_RenderList * renderList, CB_RenderList * solidList, double x, double y, double z);
        static void init();

        static void drawQuad(const CB_Vector3D& vertBL, const CB_Vector3D& vertBR, const CB_Vector3D& vertTR, const CB_Vector3D& vertTL);
        static void drawQuad(const CB_Vector3D& vertBL, const CB_Vector3D& vertBR, const CB_Vector3D& vertTR, const CB_Vector3D& vertTL, bool vertNormals);
        static void drawQuad(const CB_Vector3D& vertBL, const CB_Vector3D& vertBR, const CB_Vector3D& vertTR, const CB_Vector3D& vertTL, CB_Vector2D uv1, CB_Vector2D uv2);
        static void drawQuad(const CB_Vector3D& vertBL, const CB_Vector3D& vertBR, const CB_Vector3D& vertTR, const CB_Vector3D& vertTL, CB_Vector2D uv1, CB_Vector2D uv2, bool vertNormals);

        static CB_Face createQuad(const CB_Vector3D& vertBL, const CB_Vector3D& vertBR, const CB_Vector3D& vertTR, const CB_Vector3D& vertTL, CB_Vector2D uv1, CB_Vector2D uv2, bool vertNormals);
    protected:
    private:
        static map<uint32_t,CB_Renderer*> renderMap;
        static map<string, uint32_t> strToRenderMap;
        static CB_RenderList renderDataList;
        static CB_RenderList renderSolidList;
        static SDL_mutex * sRenderMutex;
};

#endif // CB_RENDERER_H
