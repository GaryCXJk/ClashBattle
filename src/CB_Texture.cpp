#include "CB_Texture.h"

map<string,CB_Texture*> CB_Texture::textureMap;

CB_Texture::CB_Texture()
{
    //ctor
}

CB_Texture::~CB_Texture()
{
    //dtor
}

CB_Texture * CB_Texture::addTexture(string id, GLuint texture)
{
    return addTexture(id, texture, 0, 0);
}

CB_Texture * CB_Texture::addTexture(string id, GLuint texture, uint32_t w, uint32_t h)
{
    CB_Texture * tex = new CB_Texture();
    tex->texture = texture;
    tex->width = w;
    tex->height = h;
    textureMap[id] = tex;
    return tex;
}

CB_Texture * CB_Texture::createTexture(string id, SDL_Surface * surface, GLint pMin, GLint pMag)
{
    return createTexture(id, surface, pMin, pMag, GL_REPEAT, GL_REPEAT);
}

CB_Texture * CB_Texture::createTexture(string id, SDL_Surface * surface, GLint pMin, GLint pMag, GLint wrapS, GLint wrapT)
{
    map<GLenum,GLfloat> dataFloat;
    map<GLenum,GLint> dataInt;

    dataInt[GL_TEXTURE_MIN_FILTER] = pMin;
    dataInt[GL_TEXTURE_MAG_FILTER] = pMag;
    dataInt[GL_TEXTURE_WRAP_S] = wrapS;
    dataInt[GL_TEXTURE_WRAP_T] = wrapT;
    return createTexture(id, surface, dataFloat, dataInt);
}

CB_Texture * CB_Texture::createTexture(string id, SDL_Surface * surface, map<GLenum, GLfloat> dataFloat, map<GLenum, GLint> dataInt)
{
    if(!surface)
    {
        return 0;
    }
    GLuint texture;
    GLenum textureFormat;
    GLint colNum = surface->format->BytesPerPixel;
    if(colNum == 4)
    {
        if(surface->format->Rmask == 0x000000ff)
        {
            textureFormat = GL_RGBA;
        }
        else
        {
            textureFormat = GL_BGRA;
        }
    }
    else if(colNum == 3)
    {

        if(surface->format->Rmask == 0x000000ff)
        {
            textureFormat = GL_RGB;
        }
        else
        {
            textureFormat = GL_BGR;
        }
    }
    else
    {
        return 0;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    map<GLenum, GLfloat>::iterator fIt;
    map<GLenum, GLint>::iterator iIt;
    for(fIt = dataFloat.begin(); fIt != dataFloat.end(); fIt++)
    {
        glTexParameterf(GL_TEXTURE_2D, (*fIt).first, (*fIt).second);
    }
    for(iIt = dataInt.begin(); iIt != dataInt.end(); iIt++)
    {
        glTexParameteri(GL_TEXTURE_2D, (*iIt).first, (*iIt).second);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, colNum, surface->w, surface->h, 0, textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

    return addTexture(id, texture, surface->w, surface->h);
}

CB_Texture * CB_Texture::getTexture(string id)
{
    if(textureMap.count(id) == 0)
    {
        return 0;
    }
    return textureMap[id];
}

void CB_Texture::bindTexture(string id)
{
    if(textureMap.count(id) != 0)
    {
        glBindTexture(GL_TEXTURE_2D, textureMap[id]->texture);
    }
}
