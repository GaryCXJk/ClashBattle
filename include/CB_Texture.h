#ifndef CB_TEXTURE_H
#define CB_TEXTURE_H
#include "ClashBattle.h"

class CB_Texture
{
    public:
        static CB_Texture * addTexture(string,GLuint);
        static CB_Texture * addTexture(string,GLuint,uint32_t,uint32_t);
        static CB_Texture * createTexture(string,SDL_Surface*,GLint,GLint);
        static CB_Texture * createTexture(string,SDL_Surface*,GLint,GLint,GLint,GLint);
        static CB_Texture * createTexture(string,SDL_Surface*,map<GLenum,GLfloat>,map<GLenum,GLint>);
        static CB_Texture * getTexture(string);
        static void bindTexture(string);
        uint32_t getWidth(){return width;};
        uint32_t getHeight(){return height;};
        GLuint getTextureId(){return texture;};
        void bind(){glBindTexture(GL_TEXTURE_2D, texture);};
    protected:
    private:
        CB_Texture();
        virtual ~CB_Texture();

        static map<string,CB_Texture*> textureMap;
        GLuint texture;
        uint32_t width;
        uint32_t height;
};

#endif // CB_TEXTURE_H
