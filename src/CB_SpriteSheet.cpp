#include "CB_SpriteSheet.h"

map<uint32_t,CB_SpriteSheet*> CB_SpriteSheet::sheetMap;
map<string,uint32_t> CB_SpriteSheet::strToSheetMap;

CB_SpriteSheet::CB_SpriteSheet()
{
    //ctor
}

CB_SpriteSheet::~CB_SpriteSheet()
{
    //dtor
}

uint32_t CB_SpriteSheet::createSpriteSheet()
{
    return registerSpriteSheet(new CB_SpriteSheet());
}

uint32_t CB_SpriteSheet::createSpriteSheet(string name)
{
    uint32_t id = createSpriteSheet();
    strToSheetMap[name] = id;
    return id;
}

uint32_t CB_SpriteSheet::registerSpriteSheet(CB_SpriteSheet * sheet)
{
    uint32_t idx = sheetMap.size();
    while(sheetMap.count(idx) != 0)
    {
        idx++;
    }
    sheetMap[idx] = sheet;
    return idx;
}

uint32_t CB_SpriteSheet::registerSpriteSheet(CB_SpriteSheet * sheet, string name)
{
    uint32_t id = registerSpriteSheet(sheet);
    strToSheetMap[name] = id;
    return id;
}

uint32_t CB_SpriteSheet::addTexture(CB_Texture * tex)
{
    uint32_t idx = textureMap.size();
    while(textureMap.count(idx) != 0)
    {
        idx++;
    }
    textureMap[idx] = tex;
    return idx;
}

uint32_t CB_SpriteSheet::addTexture(string name, CB_Texture * tex)
{
    uint32_t idx = addTexture(tex);
    strToTextureMap[name] = idx;
    return idx;
}

uint32_t CB_SpriteSheet::getTextureId(string name)
{
    if(strToTextureMap.count(name) == 0)
    {
        return 0;
    }
    return strToTextureMap[name];
}

CB_Texture * CB_SpriteSheet::getTexture(uint32_t id)
{
    if(textureMap.count(id) == 0)
    {
        return 0;
    }
    return textureMap[id];
}

uint32_t CB_SpriteSheet::addFrame(uint32_t textureId, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    return addFrame(textureId, x, y, width, height, 0, 0);
}

uint32_t CB_SpriteSheet::addFrame(uint32_t textureId, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t xOrig, uint32_t yOrig)
{
    CB_SpriteFrame frame;
    frame.texture = textureId;
    frame.x = x;
    frame.y = y;
    frame.width = width;
    frame.height = height;
    frame.xOrig = xOrig;
    frame.yOrig = yOrig;
    return addFrame(frame);
}

uint32_t CB_SpriteSheet::addFrame(CB_SpriteFrame frame)
{
    uint32_t idx = frameMap.size();
    while(frameMap.count(idx) != 0)
    {
        idx++;
    }
    frameMap[idx] = frame;
    return idx;
}

uint32_t CB_SpriteSheet::addFrame(string name, uint32_t textureId, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    return addFrame(name, textureId, x, y, width, height, 0, 0);
}

uint32_t CB_SpriteSheet::addFrame(string name, uint32_t textureId, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t xOrig, uint32_t yOrig)
{
    uint32_t idx = addFrame(textureId, x, y, width, height, xOrig, yOrig);
    strToFrameMap[name] = idx;
    return idx;
}

uint32_t CB_SpriteSheet::addFrame(string name, CB_SpriteFrame frame)
{
    uint32_t idx = addFrame(frame);
    strToFrameMap[name] = idx;
    return idx;
}

CB_SpriteFrame * CB_SpriteSheet::getFrame(uint32_t frameId)
{
    if(frameMap.count(frameId) == 0)
    {
        return 0;
    }
    return &frameMap[frameId];
}

CB_SpriteFrame * CB_SpriteSheet::getFrame(string name)
{
    if(strToFrameMap.count(name) == 0)
    {
        return 0;
    }
    return getFrame(strToFrameMap[name]);
}
