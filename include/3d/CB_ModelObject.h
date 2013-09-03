#ifndef CB_MODELOBJECT_H
#define CB_MODELOBJECT_H
#include "ClashBattle.h"
#include "CB_ShaderManager.h"
#include "3d/CB_Face.h"
#include "CB_Texture.h"

class CB_ModelObject
{
    public:
        CB_ModelObject();
        virtual ~CB_ModelObject();
        void setTexture(CB_Texture * _texture){texture = _texture;};
        void render();
        void renderShader();
        void addFace(CB_Face);
        void preset();
    protected:
    private:
        vector<CB_Face> faces;
        CB_Texture * texture;
        size_t vertCount;
        size_t indCount;
        size_t minCount;
        GLuint vertexVBOID;
        GLuint indexVBOID;
        GLuint displayList;
        bool hasPrerendered;
};

#endif // CB_MODELOBJECT_H
