#ifndef CB_FACE_H
#define CB_FACE_H
#include "3d/CB_Vertex.h"
#include "util/CB_Vector2D.h"
#include "CB_Texture.h"

struct CB_VertexData
{
    float posX;
    float posY;
    float posZ;
    float norX;
    float norY;
    float norZ;
    float texX;
    float texY;
    uint8_t colR;
    uint8_t colG;
    uint8_t colB;
    uint8_t colA;
    float padding[7];

    bool operator==(CB_VertexData other)
    {
        return (
                posX == other.posX &&
                posY == other.posY &&
                posZ == other.posZ &&
                norX == other.norX &&
                norY == other.norY &&
                norZ == other.norZ &&
                texX == other.texX &&
                texY == other.texY &&
                colR == other.colR &&
                colG == other.colG &&
                colB == other.colB &&
                colA == other.colA
                );
    }
};

class CB_Face
{
    public:
        CB_Face();
        virtual ~CB_Face();
        void setVertices(vector<CB_Vertex> _vertices){vertices = _vertices;};
        void setTexCoords(vector<CB_Vector2D> _texCoords){texCoords = _texCoords;};
        void setTexture(CB_Texture * _texture){texture = _texture;};
        void setColor(uint32_t _color){color = _color;};
        size_t size(){if(count > 0) return count; return vertices.size();};
        void render();
        vector<CB_VertexData> prerender();
        void preset();
        void preset(vector<CB_VertexData>);
    protected:
    private:
        vector<CB_Vertex> vertices;
        vector<CB_Vector2D> texCoords;
        CB_Texture * texture;
        uint32_t color;
        size_t count;
        GLuint vertexVBOID;
        GLuint indexVBOID;
};

#endif // CB_FACE_H
