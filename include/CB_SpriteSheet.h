#ifndef CB_SPRITESHEET_H
#define CB_SPRITESHEET_H
#include "ClashBattle.h"
#include "CB_Texture.h"

struct CB_SpriteFrame
{
    uint32_t texture;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    uint32_t xOrig;
    uint32_t yOrig;
};

struct CB_AnimFrame
{
    uint32_t frameID;
    int32_t duration;
};

typedef vector<CB_AnimFrame> CB_AnimSequence;

class CB_SpriteSheet
{
    public:
        CB_SpriteSheet();
        virtual ~CB_SpriteSheet();
        static uint32_t createSpriteSheet();
        static uint32_t createSpriteSheet(string name);
        static uint32_t registerSpriteSheet(CB_SpriteSheet * sheet);
        static uint32_t registerSpriteSheet(CB_SpriteSheet * sheet, string name);
        static CB_SpriteSheet * getSpriteSheet(uint32_t id){if(sheetMap.count(id) == 0) return 0; return sheetMap[id];};
        static CB_SpriteSheet * getSpriteSheet(string name){if(strToSheetMap.count(name) == 0 || sheetMap.count(strToSheetMap[name]) == 0) return 0; return sheetMap[strToSheetMap[name]];};
        uint32_t addTexture(CB_Texture*);
        uint32_t addTexture(string name, CB_Texture * tex);
        uint32_t getTextureId(string name);
        CB_Texture * getTexture(uint32_t id);
        uint32_t addFrame(uint32_t textureId, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        uint32_t addFrame(uint32_t textureId, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t xOrig, uint32_t yOrig);
        uint32_t addFrame(CB_SpriteFrame frame);
        uint32_t addFrame(string name, uint32_t textureId, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        uint32_t addFrame(string name, uint32_t textureId, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t xOrig, uint32_t yOrig);
        uint32_t addFrame(string name, CB_SpriteFrame frame);
        CB_SpriteFrame * getFrame(uint32_t frameId);
        CB_SpriteFrame * getFrame(string name);
    protected:
    private:
        map<uint32_t,CB_Texture*> textureMap;
        map<uint32_t,CB_SpriteFrame> frameMap;
        map<string,uint32_t> strToTextureMap;
        map<string,uint32_t> strToFrameMap;

        static map<uint32_t,CB_SpriteSheet*> sheetMap;
        static map<string,uint32_t> strToSheetMap;
};

#endif // CB_SPRITESHEET_H
