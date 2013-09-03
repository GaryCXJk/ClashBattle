#ifndef CB_FONT_H
#define CB_FONT_H
#include "ClashBattle.h"
#include "CB_SpriteSheet.h"

struct CB_FontGlyph
{
    uint32_t texture;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    uint32_t yBase;
};

class CB_Font
{
    public:
        CB_Font();
        virtual ~CB_Font();
        static uint32_t createFont();
        static uint32_t createFont(string fontName);
        static uint32_t registerFont(CB_Font * font);
        static uint32_t registerFont(CB_Font * font, string name);
        static CB_Font * getFont(uint32_t id);
        static CB_Font * getFont(string name);
        uint32_t addTexture(CB_Texture*);
        uint32_t addTexture(string name, CB_Texture * tex);
        uint32_t getTextureId(string name);
        CB_Texture * getTexture(uint32_t id);
        void setNewLineHeight(uint32_t _newLineHeight);
        void setSpaceWidth(uint32_t _spaceWidth);
        void setCharSpacing(size_t _charSpacing);
        void addGlyph(uint32_t index, uint32_t textureId, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t yBase);
        void addGlyph(uint32_t index, CB_FontGlyph glyph);
        size_t getStringHeight(string str);
        size_t getStringWidth(string str);
        size_t getStringWidth(string str, CB_StringEncoding encoding);
        void drawString(string str, double x, double y);
        void drawString(string str, double x, double y, CB_StringEncoding encoding);
    protected:
    private:
        map<uint32_t,CB_Texture*> textureMap;
        map<uint32_t,CB_FontGlyph> glyphMap;
        map<string,uint32_t> strToTextureMap;
        uint32_t newLineHeight;
        uint32_t spaceWidth;
        size_t charSpacing;

        SDL_mutex * fontMutex;

        static SDL_mutex * sFontMutex;

        static map<uint32_t,CB_Font*> fontMap;
        static map<string,uint32_t> strToFontMap;
};

#endif // CB_FONT_H
