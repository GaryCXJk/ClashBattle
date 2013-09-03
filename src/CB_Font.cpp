#include "CB_Font.h"

SDL_mutex * CB_Font::sFontMutex = SDL_CreateMutex();
map<uint32_t,CB_Font*> CB_Font::fontMap;
map<string,uint32_t> CB_Font::strToFontMap;

CB_Font::CB_Font()
{
    fontMutex = SDL_CreateMutex();
}

CB_Font::~CB_Font()
{
    //dtor
}

uint32_t CB_Font::createFont()
{
    return registerFont(new CB_Font());
}

uint32_t CB_Font::createFont(string name)
{
    uint32_t id = createFont();
    SDL_mutexP(sFontMutex);
    strToFontMap[name] = id;
    SDL_mutexV(sFontMutex);
    return id;
}

uint32_t CB_Font::registerFont(CB_Font * font)
{

    uint32_t idx;
    SDL_mutexP(sFontMutex);
    idx = fontMap.size();
    while(fontMap.count(idx) != 0)
    {
        idx++;
    }
    fontMap[idx] = font;
    SDL_mutexV(sFontMutex);
    return idx;
}

uint32_t CB_Font::registerFont(CB_Font * font, string name)
{
    uint32_t id = registerFont(font);
    SDL_mutexP(sFontMutex);
    strToFontMap[name] = id;
    SDL_mutexV(sFontMutex);
    return id;
}

CB_Font * CB_Font::getFont(uint32_t id)
{
    CB_Font * retFont = 0;
    SDL_mutexP(sFontMutex);
    if(fontMap.count(id) != 0)
    {
        retFont = fontMap[id];
    }
    SDL_mutexV(sFontMutex);
    return retFont;
}

CB_Font * CB_Font::getFont(string name)
{
    CB_Font * retFont = 0;
    SDL_mutexP(sFontMutex);
    if(strToFontMap.count(name) != 0 && fontMap.count(strToFontMap[name]) != 0)
    {
        retFont = fontMap[strToFontMap[name]];
    }
    SDL_mutexV(sFontMutex);
    return retFont;
}

uint32_t CB_Font::addTexture(CB_Texture * tex)
{
    uint32_t idx;
    SDL_mutexP(fontMutex);
    idx = textureMap.size();
    while(textureMap.count(idx) != 0)
    {
        idx++;
    }
    textureMap[idx] = tex;
    SDL_mutexV(fontMutex);
    return idx;
}

uint32_t CB_Font::addTexture(string name, CB_Texture * tex)
{
    uint32_t idx = addTexture(tex);
    SDL_mutexP(fontMutex);
    strToTextureMap[name] = idx;
    SDL_mutexV(fontMutex);
    return idx;
}

uint32_t CB_Font::getTextureId(string name)
{
    uint32_t texId = 0;
    SDL_mutexP(fontMutex);
    if(strToTextureMap.count(name) != 0)
    {
        texId = strToTextureMap[name];
    }
    SDL_mutexV(fontMutex);
    return texId;
}

CB_Texture * CB_Font::getTexture(uint32_t id)
{
    CB_Texture * retTex = 0;
    SDL_mutexP(fontMutex);
    if(textureMap.count(id) != 0)
    {
        retTex = textureMap[id];
    }
    SDL_mutexV(fontMutex);
    return retTex;
}

void CB_Font::setNewLineHeight(uint32_t _newLineHeight)
{
    SDL_mutexP(fontMutex);
    newLineHeight = _newLineHeight;
    SDL_mutexV(fontMutex);
}

void CB_Font::setSpaceWidth(uint32_t _spaceWidth)
{
    SDL_mutexP(fontMutex);
    spaceWidth = _spaceWidth;
    SDL_mutexV(fontMutex);
}

void CB_Font::setCharSpacing(uint32_t _charSpacing)
{
    SDL_mutexP(fontMutex);
    charSpacing = _charSpacing;
    SDL_mutexV(fontMutex);
}

void CB_Font::addGlyph(uint32_t index, uint32_t textureId, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t yBase)
{
    CB_FontGlyph glyph;
    glyph.texture = textureId;
    glyph.x = x;
    glyph.y = y;
    glyph.width = width;
    glyph.height = height;
    glyph.yBase = yBase;
    addGlyph(index, glyph);
}

void CB_Font::addGlyph(uint32_t index, CB_FontGlyph glyph)
{
    SDL_mutexP(fontMutex);
    glyphMap[index] = glyph;
    SDL_mutexV(fontMutex);
}

size_t CB_Font::getStringHeight(string str)
{
    SDL_mutexP(fontMutex);
    uint32_t _newLineHeight = newLineHeight;
    SDL_mutexV(fontMutex);

    uint32_t numLines = 1;
    uint32_t newPos = 0;
    while(true)
    {
        size_t crlfPos = str.find("\r\n", newPos);
        size_t lfPos = str.find("\n", newPos);
        size_t crPos = str.find("\r", newPos);
        if(crlfPos != string::npos && crlfPos < lfPos && crlfPos < crPos)
        {
            newPos = crlfPos + 2;
            numLines++;
            continue;
        }
        if(lfPos != string::npos && lfPos < crPos)
        {
            newPos = lfPos + 1;
            numLines++;
            continue;
        }
        if(crPos != string::npos)
        {
            newPos = crPos + 1;
            numLines++;
            continue;
        }
        break;
    }
    return numLines * _newLineHeight;
}

size_t CB_Font::getStringWidth(string str)
{
    return getStringWidth(str, CB_STRING_ENCODING_ASCII);
}

size_t CB_Font::getStringWidth(string str, CB_StringEncoding encoding)
{
    SDL_mutexP(fontMutex);
    uint32_t _spaceWidth = spaceWidth;
    uint32_t _charSpacing = charSpacing;
    map<uint32_t, CB_FontGlyph> glyphs = glyphMap;
    SDL_mutexV(fontMutex);

    int strSize = 0;
    size_t maxSize = 0;
    size_t curSize = 0;

    int i = 0;
    int iMax = str.length();

    while(i < iMax)
    {
        strSize++;
        uint32_t glyph = 0;
        int sBytes = 1;
        switch(encoding)
        {
            case CB_STRING_ENCODING_ASCII:
            {
                glyph = str[i];
                break;
            }
            case CB_STRING_ENCODING_UTF8:
            {
                if(str[i] > 0x7F)
                {
                    int iB = 6;
                    while((str[i] & (1 << iB)) > 0 && iB > 1)
                    {
                        iB--;
                    }
                    if(iB > 1)
                    {
                        glyph = str[i] & ((1 << iB) - 1);
                        iB = 6 - iB;
                        sBytes += iB;
                        for(int iC = 0; iC < iB; iC++)
                        {
                            glyph = (glyph << 6) | (str[i + 1 + iC] & 0x3F);
                        }
                    }
                }
                else
                {
                    glyph = str[i];
                }
                break;
            }
        }
        if(glyph == '\r')
        {
            if(str[i + 1] == '\n')
            {
                sBytes++;
            }
        }
        i+= sBytes;
        if(glyph == '\r' || glyph == '\n')
        {
            curSize+= (strSize - 1) * _charSpacing;
            if(curSize > maxSize)
            {
                maxSize = curSize;
            }
            strSize = 0;
            curSize = 0;
            continue;
        }
        if(glyph == ' ')
        {
            curSize+= _spaceWidth;
            continue;
        }
        if(glyphs.count(glyph) == 0)
        {
            strSize--;
            continue;
        }
        curSize+= glyphs[glyph].width;
    }

    curSize+= (strSize - 1) * _charSpacing;
    if(curSize > maxSize)
    {
        maxSize = curSize;
    }

    return maxSize;
}

void CB_Font::drawString(string str, double x, double y)
{
    drawString(str, x, y, CB_STRING_ENCODING_ASCII);
}

void CB_Font::drawString(string str, double x, double y, CB_StringEncoding encoding)
{
    SDL_mutexP(fontMutex);
    uint32_t _newLineHeight = newLineHeight;
    uint32_t _spaceWidth = spaceWidth;
    uint32_t _charSpacing = charSpacing;
    map<uint32_t, CB_FontGlyph> glyphs = glyphMap;
    SDL_mutexV(fontMutex);

    int strSize = 0;
    int i = 0;
    int iMax = str.length();
    double xPos = x;
    double yPos = y;

    while(i < iMax)
    {
        strSize++;
        uint32_t glyph = 0;
        int sBytes = 1;
        switch(encoding)
        {
            case CB_STRING_ENCODING_ASCII:
            {
                glyph = str[i];
                break;
            }
            case CB_STRING_ENCODING_UTF8:
            {
                if(str[i] > 0x7F)
                {
                    int iB = 6;
                    while((str[i] & (1 << iB)) > 0 && iB > 1)
                    {
                        iB--;
                    }
                    if(iB > 1)
                    {
                        glyph = str[i] & ((1 << iB) - 1);
                        iB = 6 - iB;
                        sBytes += iB;
                        for(int iC = 0; iC < iB; iC++)
                        {
                            glyph = (glyph << 6) | (str[i + 1 + iC] & 0x3F);
                        }
                    }
                }
                else
                {
                    glyph = str[i];
                }
                break;
            }
        }
        if(glyph == '\r')
        {
            if(str[i + 1] == '\n')
            {
                sBytes++;
            }
        }
        i+= sBytes;
        if(glyph == '\r' || glyph == '\n')
        {
            strSize = 0;
            xPos = x;
            yPos-= _newLineHeight;
            continue;
        }
        if(strSize > 1)
        {
            xPos+= _charSpacing;
        }
        if(glyph == ' ')
        {
            xPos+= _spaceWidth;
            continue;
        }
        if(glyphs.count(glyph) == 0)
        {
            strSize--;
            xPos-= _charSpacing;
            continue;
        }
        CB_FontGlyph curGlyph = glyphs[glyph];
        bool isTexEnabled = (glIsEnabled(GL_TEXTURE_2D) == GL_TRUE);
        glEnable(GL_TEXTURE_2D);
        CB_Texture * cTex = getTexture(curGlyph.texture);
        cTex->bind();
        double tWidth = cTex->getWidth();
        double tHeight = cTex->getHeight();
        double gW = curGlyph.width;
        double gH = curGlyph.height;
        double u1 = curGlyph.x / tWidth;
        double v1 = curGlyph.y / tHeight;
        double u2 = (curGlyph.x + gW) / tWidth;
        double v2 = (curGlyph.y + gH) / tHeight;
        double yBase = curGlyph.yBase;
        glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2d(u1, v1);
        glVertex2d(xPos, yPos + yBase);
        glTexCoord2d(u1, v2);
        glVertex2d(xPos, yPos + yBase - gH);
        glTexCoord2d(u2, v2);
        glVertex2d(xPos + gW, yPos + yBase - gH);
        glTexCoord2d(u2, v1);
        glVertex2d(xPos + gW, yPos + yBase);
        glEnd();
        if(!isTexEnabled)
        {
            glDisable(GL_TEXTURE_2D);
        }
        xPos+= gW;
    }
    glyphs.clear();
}
