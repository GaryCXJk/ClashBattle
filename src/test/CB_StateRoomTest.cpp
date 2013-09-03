#include "test/CB_StateRoomTest.h"
#include "CB_StateManager.h"

CB_StateRoomTest::CB_StateRoomTest()
{
    //ctor
}

CB_StateRoomTest::~CB_StateRoomTest()
{
    //dtor
}


void CB_StateRoomTest::start()
{
    //CB_FPS::get(CB_FPS_RENDER)->setTargetFPS(600);
    speed = -1.0 / 30;
    interpolation = 0.0;
    uint32_t camId = CB_Camera::createCamera();
    CB_Screen::setCamera(camId);
    CB_Screen::setSize(320, 240);
    CB_Screen::setFov(45);
    CB_Screen::getCamera()->setPosition(160, 120, 0);
    pos.x = 160;
    pos.y = 120;
    zoom = 1.0;
    resetTime = -1.0;

    room = new CB_Room(52, 27, 1, 1, 51, 26, 16);
    tileSolid = new CB_Tile(16, 16, CB_COLLISION_SOLID);
    CB_Tile * tileZone = new CB_Tile(16, 16, CB_COLLISION_ZONE);
    tileWide = new CB_Tile(32, 16, CB_COLLISION_SOLID);
    tileHigh = new CB_Tile(16, 32, CB_COLLISION_SOLID);
    tileBig2x2 = new CB_Tile(32, 32, CB_COLLISION_SOLID);
    tileDrop = new CB_Tile(16, 16, CB_COLLISION_DROPTHROUGH, CB_COLLISION_NONE, CB_COLLISION_NONE, CB_COLLISION_NONE);

    room->addTile(2, 2, tileSolid);
    room->addTile(2, 3, tileSolid);
    room->addTile(3, 3, tileSolid);
    room->addTile(3, 2, tileZone);
    room->addTile(8, 2, tileDrop);
    room->addTile(9, 2, tileDrop);
    room->addTile(9, 3, tileDrop);
    room->addTile(10, 3, tileDrop);
    room->addTile(11, 3, tileDrop);
    room->addTile(5, 2, tileWide);
    room->addTile(6, 3, tileWide);
    room->addTile(5, 4, tileWide);
    room->addTile(6, 5, tileWide);
    room->addTile(8, 4, tileHigh);
    room->addTile(2, 14, tileSolid);
    room->addTile(2, 15, tileSolid);
    room->addTile(2, 16, tileSolid);
    room->addTile(2, 17, tileSolid);
    room->addTile(2, 18, tileSolid);
    room->addTile(3, 16, tileSolid);
    room->addTile(4, 16, tileSolid);
    room->addTile(5, 16, tileSolid);
    room->addTile(6, 14, tileSolid);
    room->addTile(6, 15, tileSolid);
    room->addTile(6, 16, tileSolid);
    room->addTile(6, 17, tileSolid);
    room->addTile(6, 18, tileSolid);
    room->addTile(10, 14, tileSolid);
    room->addTile(9, 15, tileSolid);
    room->addTile(11, 15, tileSolid);
    room->addTile(8, 16, tileSolid);
    room->addTile(8, 17, tileSolid);
    room->addTile(8, 18, tileSolid);
    room->addTile(9, 16, tileSolid);
    room->addTile(10, 16, tileSolid);
    room->addTile(11, 16, tileSolid);
    room->addTile(12, 16, tileSolid);
    room->addTile(12, 17, tileSolid);
    room->addTile(12, 18, tileSolid);
    room->addTile(14, 14, tileSolid);
    room->addTile(14, 15, tileSolid);
    room->addTile(14, 16, tileSolid);
    room->addTile(14, 17, tileSolid);
    room->addTile(14, 18, tileSolid);
    room->addTile(15, 18, tileSolid);
    room->addTile(16, 18, tileSolid);
    room->addTile(17, 18, tileSolid);
    room->addTile(18, 18, tileSolid);
    room->addTile(20, 14, tileSolid);
    room->addTile(20, 15, tileSolid);
    room->addTile(20, 16, tileSolid);
    room->addTile(20, 17, tileSolid);
    room->addTile(20, 18, tileSolid);
    room->addTile(21, 14, tileSolid);
    room->addTile(22, 14, tileSolid);
    room->addTile(23, 15, tileSolid);
    room->addTile(24, 16, tileSolid);
    room->addTile(23, 17, tileSolid);
    room->addTile(22, 18, tileSolid);
    room->addTile(21, 18, tileSolid);
    room->addTile(26, 16, tileSolid);
    room->addTile(27, 15, tileSolid);
    room->addTile(27, 17, tileSolid);
    room->addTile(28, 14, tileSolid);
    room->addTile(28, 18, tileSolid);
    room->addTile(29, 15, tileSolid);
    room->addTile(29, 17, tileSolid);
    room->addTile(30, 16, tileSolid);

    room->optimize();

    bounds = room->getBounds();
}

void CB_StateRoomTest::prerender()
{
    sheet = new CB_SpriteSheet();
    SDL_Surface * surface = IMG_Load("testsheet.png");
    CB_Texture::createTexture("sheet", surface, GL_NEAREST, GL_NEAREST, GL_CLAMP, GL_CLAMP);
    SDL_FreeSurface(surface);
    sheet->addTexture("sheet", CB_Texture::getTexture("sheet"));
    sheet->addFrame("regular", sheet->getTextureId("sheet"), 0, 0, 16, 16);
    sheet->addFrame("h_left", sheet->getTextureId("sheet"), 64, 0, 16, 16);
    sheet->addFrame("h_center", sheet->getTextureId("sheet"), 80, 0, 16, 16);
    sheet->addFrame("h_right", sheet->getTextureId("sheet"), 96, 0, 16, 16);
    sheet->addFrame("v_top", sheet->getTextureId("sheet"), 0, 16, 16, 16);
    sheet->addFrame("v_center", sheet->getTextureId("sheet"), 0, 32, 16, 16);
    sheet->addFrame("v_bottom", sheet->getTextureId("sheet"), 0, 48, 16, 16);
    sheet->addFrame("split_cross", sheet->getTextureId("sheet"), 80, 32, 16, 16);
    sheet->addFrame("split_left", sheet->getTextureId("sheet"), 112, 32, 16, 16);
    sheet->addFrame("split_right", sheet->getTextureId("sheet"), 144, 32, 16, 16);
    sheet->addFrame("split_top", sheet->getTextureId("sheet"), 128, 16, 16, 16);
    sheet->addFrame("split_bottom", sheet->getTextureId("sheet"), 128, 48, 16, 16);
    sheet->addFrame("circle", sheet->getTextureId("sheet"), 32, 48, 16, 16);
    sheet->addFrame("platform", sheet->getTextureId("sheet"), 48, 48, 16, 3);
    sheet->addFrame("pillar", sheet->getTextureId("sheet"), 224, 0, 32, 112, 16, 56);
    sheet->addFrame("big_tl", sheet->getTextureId("sheet"), 16, 0, 16, 16);
    sheet->addFrame("big_top", sheet->getTextureId("sheet"), 32, 0, 16, 16);
    sheet->addFrame("big_tr", sheet->getTextureId("sheet"), 48, 0, 16, 16);
    sheet->addFrame("big_left", sheet->getTextureId("sheet"), 16, 16, 16, 16);
    sheet->addFrame("big_center", sheet->getTextureId("sheet"), 32, 16, 16, 16);
    sheet->addFrame("big_right", sheet->getTextureId("sheet"), 48, 16, 16, 16);
    sheet->addFrame("big_bl", sheet->getTextureId("sheet"), 16, 32, 16, 16);
    sheet->addFrame("big_bottom", sheet->getTextureId("sheet"), 32, 32, 16, 16);
    sheet->addFrame("big_br", sheet->getTextureId("sheet"), 48, 32, 16, 16);
    sheet->addTexture("sheet", CB_Texture::getTexture("sheet"));

    CB_BoxRenderer * box = (CB_BoxRenderer*)CB_Renderer::getRenderer("box");
    CB_SpriteRenderer * sprite = (CB_SpriteRenderer*)CB_Renderer::getRenderer("sprite");
    CB_GroupRenderer * groupR = (CB_GroupRenderer*)CB_Renderer::getRenderer("group");
    CB_DepthScaleRenderer * dsR = (CB_DepthScaleRenderer*)CB_Renderer::getRenderer("depthscale");
    string solidRelSides[] = {"regular", "regular", "regular", "regular", "regular", "regular"};
    string dropRelSides[] = {"platform", "platform", "platform", "regular", "regular", "platform"};
    CB_RenderDataRel solidRel = box->getBox(8, -8, 0, -8, -8, -8, 16, 16, 16, sheet, solidRelSides, true);
    CB_RenderDataRel dropRel = box->prerender(box->getBox(8, -8, 0, -8, 5, -8, 16, 3, 16, sheet, dropRelSides, true));
    solidRel.tileSize = 16;
    solidRel.sharedUserdata = true;
    dropRel.tileSize = 16;

    string wideLSides[] = {"h_right", "regular", "split_cross", "h_left", "h_right", "h_left"};
    string wideRSides[] = {"h_left", "split_cross", "regular", "h_right", "h_left", "h_right"};
    string highUSides[] = {"v_top", "v_top", "v_top", "regular", "split_cross", "v_top"};
    string highDSides[] = {"v_bottom", "v_bottom", "v_bottom", "split_cross", "regular", "v_bottom"};
    string bigULSides[] = {"big_tr", "v_top", "split_top", "h_left", "split_right", "big_tl"};
    string bigUSides[] = {"big_top", "split_top", "split_top", "h_center", "big_center", "big_top"};
    string bigURSides[] = {"big_tl", "split_top", "v_top", "h_right", "split_left", "big_tr"};
    string bigLSides[] = {"big_right", "v_center", "big_center", "split_left", "split_right", "big_left"};
    string bigCSides[] = {"big_center", "big_center", "big_center", "big_center", "big_center", "big_center"};
    string bigRSides[] = {"big_left", "v_center", "big_center", "split_right", "split_left", "big_right"};
    string bigDLSides[] = {"big_br", "v_bottom", "split_bottom", "split_left", "h_right", "big_bl"};
    string bigDSides[] = {"big_bottom", "split_bottom", "split_bottom", "big_center", "h_center", "big_bottom"};
    string bigDRSides[] = {"big_bl", "split_bottom", "v_bottom", "split_right", "h_left", "big_br"};
    CB_RenderDataRel wideL = box->prerender(box->getBox(8, -8, 0, -8, -8, -8, 16, 16, 16, sheet, wideLSides, true));
    CB_RenderDataRel wideR = box->prerender(box->getBox(24, -8, 0, -8, -8, -8, 16, 16, 16, sheet, wideRSides, true));
    CB_RenderDataRel highU = box->prerender(box->getBox(8, -8, 0, -8, -8, -8, 16, 16, 16, sheet, highUSides, true));
    CB_RenderDataRel highD = box->prerender(box->getBox(8, -24, 0, -8, -8, -8, 16, 16, 16, sheet, highDSides, true));
    CB_RenderDataRel bigUL = box->prerender(box->getBox(8, -8, 0, -8, -8, -8, 16, 16, 16, sheet, bigULSides, true));
    CB_RenderDataRel bigU = box->prerender(box->getBox(8, -8, 0, -8, -8, -8, 16, 16, 16, sheet, bigUSides, true));
    CB_RenderDataRel bigUR = box->prerender(box->getBox(8, -8, 0, -8, -8, -8, 16, 16, 16, sheet, bigURSides, true));
    CB_RenderDataRel bigL = box->prerender(box->getBox(8, -8, 0, -8, -8, -8, 16, 16, 16, sheet, bigLSides, true));
    CB_RenderDataRel bigC = box->prerender(box->getBox(8, -8, 0, -8, -8, -8, 16, 16, 16, sheet, bigCSides, true));
    CB_RenderDataRel bigR = box->prerender(box->getBox(8, -8, 0, -8, -8, -8, 16, 16, 16, sheet, bigRSides, true));
    CB_RenderDataRel bigDL = box->prerender(box->getBox(8, -8, 0, -8, -8, -8, 16, 16, 16, sheet, bigDLSides, true));
    CB_RenderDataRel bigD = box->prerender(box->getBox(8, -8, 0, -8, -8, -8, 16, 16, 16, sheet, bigDSides, true));
    CB_RenderDataRel bigDR = box->prerender(box->getBox(8, -8, 0, -8, -8, -8, 16, 16, 16, sheet, bigDRSides, true));
    wideL.tileSize = 16;
    wideR.tileSize = 16;
    highU.tileSize = 16;
    highD.tileSize = 16;
    bigUL.tileSize = 16;
    bigU.tileSize = 16;
    bigUR.tileSize = 16;
    bigL.tileSize = 16;
    bigC.tileSize = 16;
    bigR.tileSize = 16;
    bigDL.tileSize = 16;
    bigD.tileSize = 16;
    bigDR.tileSize = 16;

    CB_RenderList wideList;
    CB_RenderList highList;
    CB_RenderList big2x2List;
    CB_RenderList big3x3List;

    CB_Renderer::listRender(wideL, &wideList);
    CB_Renderer::listRender(wideR, &wideList);
    CB_Renderer::listRender(highU, &highList);
    CB_Renderer::listRender(highD, &highList);
    CB_Renderer::listRender(bigUL, &big2x2List);
    CB_Renderer::listRender(bigUR, 16, 0, 0, &big2x2List);
    CB_Renderer::listRender(bigDL, 0, -16, 0, &big2x2List);
    CB_Renderer::listRender(bigDR, 16, -16, 0, &big2x2List);
    CB_Renderer::listRender(bigUL, &big3x3List);
    CB_Renderer::listRender(bigU, 16, 0, 0, &big3x3List);
    CB_Renderer::listRender(bigUR, 32, 0, 0, &big3x3List);
    CB_Renderer::listRender(bigL, 0, -16, 0, &big3x3List);
    CB_Renderer::listRender(bigC, 16, -16, 0, &big3x3List);
    CB_Renderer::listRender(bigR, 32, -16, 0, &big3x3List);
    CB_Renderer::listRender(bigDL, 0, -32, 0, &big3x3List);
    CB_Renderer::listRender(bigD, 16, -32, 0, &big3x3List);
    CB_Renderer::listRender(bigDR, 32, -32, 0, &big3x3List);

    CB_RenderDataRel wideGroup = groupR->getGroup(0, 0, 0, 0, 0, 0, wideList);
    CB_RenderDataRel highGroup = groupR->getGroup(0, 0, 0, 0, 0, 0, highList);
    CB_RenderDataRel big2x2Group = groupR->getGroup(0, 0, 0, 0, 0, 0, big2x2List);

    CB_RenderDataRel spriteRel = sprite->getSprite(0, 0, 0, 0, 0, 0, sheet, "pillar");
    CB_RenderDataRel depthScale = dsR->getDepthScaleRenderData(160, 120, -CB_Screen::getZ() * 2, spriteRel);
    room->addProp(depthScale);
    depthScale = dsR->getDepthScaleRenderData(160, 120, -CB_Screen::getZ() * 4, spriteRel);
    room->addProp(depthScale);
    depthScale = dsR->getDepthScaleRenderData(160, 120, -CB_Screen::getZ() * 6, spriteRel);
    room->addProp(depthScale);
    depthScale = dsR->getDepthScaleRenderData(160 + 32 / (CB_Screen::getZ() / (CB_Screen::getZ() * 7)), 120, -CB_Screen::getZ() * 6, spriteRel);
    room->addProp(depthScale);
    depthScale = dsR->getDepthScaleRenderData(160, 120, CB_Screen::getZ() / 2, solidRel, false);
    room->addProp(depthScale);
    depthScale = dsR->getDepthScaleRenderData(224, 120, CB_Screen::getZ() / 2, solidRel, true);
    room->addProp(depthScale);
    depthScale = dsR->getDepthScaleRenderData(160, 120, CB_Screen::getZ() / 4, solidRel, false);
    room->addProp(depthScale);
    depthScale = dsR->getDepthScaleRenderData(224, 120, CB_Screen::getZ() / 4, solidRel, true);
    room->addProp(depthScale);
    depthScale = dsR->getDepthScaleRenderData(160, 120, -CB_Screen::getZ(), solidRel, false);
    room->addProp(depthScale);
    depthScale = dsR->getDepthScaleRenderData(224, 120, -CB_Screen::getZ(), solidRel, true);
    room->addProp(depthScale);
    depthScale = dsR->getDepthScaleRenderData(640, 120, -CB_Screen::getZ() * 8, solidRel, true);
    room->addProp(depthScale);

    solidRel.tileSize = CB_Screen::getTileSize();
    CB_RenderDataRel solidPre = box->prerender(solidRel);
    solidRel.tileSize = 16;

    tileSolid->attachRenderData(solidPre);
    tileWide->attachRenderData(wideGroup);
    tileHigh->attachRenderData(highGroup);
    tileBig2x2->attachRenderData(big2x2Group);
    tileDrop->attachRenderData(dropRel);

    currentTile = tileSolid;
}

void CB_StateRoomTest::stop()
{

}

void CB_StateRoomTest::run()
{
    interpolation+= speed;
    interpolation = min(1.0, max(0.0, interpolation));
    zoom+= 0.0125 * (mZP - mZM);
    zoom = max(0.1, min(min(room->getScreenWidth() / CB_Screen::getWidth(), room->getScreenHeight() / CB_Screen::getHeight()),zoom));
    double w = CB_Screen::getWidth() * zoom / 2;
    double h = CB_Screen::getHeight() * zoom / 2;
    pos.x += mXR - mXL;
    pos.y += mYU - mYD;
    pos.x = max(w, min(room->getScreenWidth() - w, pos.x));
    pos.y = max(h, min(room->getScreenHeight() - h, pos.y));

    rot.y += rXR - rXL;
    rot.x += rYU - rYD;
    rot.x = max(-45.0, min(45.0, rot.x));
    rot.y = max(-45.0, min(45.0, rot.y));
    if(resetTime > -1.0)
    {
        resetTime-= 1.0 / 30;
        if(resetTime <= 0)
        {
            resetTime = -1;
            rot.x = 0;
            rot.y = 0;
            zoom = 1.0;
        }
    }
}

void CB_StateRoomTest::draw()
{
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    if(!CB_StateManager::isDeactivating())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    double rTime = (resetTime > -1 ? -cos(resetTime * PI) / 2 + 0.5 : 1);
    double rZoom = (resetTime > -1 ? zoom * rTime + 1.0 - rTime : zoom);
    double rWidth = CB_Screen::getWidth() * rZoom / 2;
    double rHeight = CB_Screen::getHeight() * rZoom / 2;
    CB_Vector3D rPos(max(rWidth, pos.x), max(rHeight, pos.y), 0);
    double iPol = -cos(interpolation * PI) / 2 + 0.5;

    CB_Screen::setOrthoZoom(rZoom);
    CB_Screen::setProjection(iPol);
    CB_Screen::getCamera()->setPosition(rPos.x, rPos.y, 0);
    CB_Screen::getCamera()->setFocalLength(CB_Screen::getZ() * rZoom);
    CB_Screen::getCamera()->setRotation(rot.x * iPol * rTime, rot.y * iPol * rTime, 0);
    CB_Screen::getCamera()->doCamera();

    glPointSize(3);
    glDepthFunc(GL_LEQUAL);

    room->prepareRender();

    vector<CB_CollisionBound*>::iterator it;

    for(it = bounds.begin(); it < bounds.end(); it++)
    {
        CB_CollisionBound * bound = *it;
        CB_Vector2D vec1 = bound->getFirst();
        CB_Vector2D vec2 = bound->getSecond();

        switch(bound->type)
        {
            case CB_COLLISION_SOLID:
                glColor3d(0.3, 0.5, 1.0);
                break;
            case CB_COLLISION_DROPTHROUGH:
                glColor3d(0.3, 1.0, 0.5);
                break;
            default:
                glColor3d(1.0, 1.0, 1.0);
                break;
        }
        glBegin(GL_LINES);
        glVertex2d(vec1.x, vec1.y);
        glVertex2d(vec2.x, vec2.y);
        glEnd();
        glBegin(GL_POINTS);
        glVertex2d(vec1.x, vec1.y);
        glVertex2d(vec2.x, vec2.y);
        glEnd();
    }

    glPointSize(5);

    double w = CB_Screen::getWidth() / 2;
    double h = CB_Screen::getHeight() / 2;
    double sH = room->getScreenHeight();
    double xL = room->getScreenLeft();
    double yT = room->getScreenTop();
    double rW = room->getWidth();
    double rH = room->getHeight();

    CB_Vector2D posVec = CB_Screen::getCameraToPlaneOnWorldZ(xMouse - w, yMouse - h, 0);

    int32_t tX = (posVec.x + xL) / 16;
    int32_t tY = (sH - posVec.y + yT) / 16;

    if(tX > -1 && tX < rW && tY > -1 && tY < rH)
    {
        glColor3d(1.0, 0.0, 0.0);
        if(room->isFree(tX, tY, currentTile))
        {
            glColor3d(0.0, 1.0, 0.0);
            currentTile->prepareRender(tX * 16 - xL, sH - tY * 16 + yT, 16);
        }

        uint8_t tileW = currentTile->getWidth(room->getTileSize());
        uint8_t tileH = currentTile->getHeight(room->getTileSize());

        glBegin(GL_POINTS);
        glVertex2d(tX * 16 - xL, sH - tY * 16 + yT);
        glVertex2d(tX * 16 - xL, sH - (tY + tileH) * 16 + yT);
        glVertex2d((tX + tileW) * 16 - xL, sH - (tY + tileH) * 16 + yT);
        glVertex2d((tX + tileW) * 16 - xL, sH - tY * 16 + yT);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glVertex2d(tX * 16 - xL, sH - tY * 16 + yT);
        glVertex2d(tX * 16 - xL, sH - (tY + tileH) * 16 + yT);
        glVertex2d((tX + tileW) * 16 - xL, sH - (tY + tileH) * 16 + yT);
        glVertex2d((tX + tileW) * 16 - xL, sH - tY * 16 + yT);
        glVertex2d(tX * 16 - xL, sH - tY * 16 + yT);
        glEnd();
    }

    CB_Renderer::process();
    CB_Screen::getCamera()->resetCamera();

    glPopMatrix();
}

void CB_StateRoomTest::onKeyDown(SDL_Keycode sym, SDL_Keymod mod)
{
    switch(sym)
    {
        case SDLK_SPACE:
        {
            speed = -speed;
            break;
        }
        case SDLK_a:
        case SDLK_LEFT:
        {
            mXL = 1;
            break;
        }
        case SDLK_d:
        case SDLK_RIGHT:
        {
            mXR = 1;
            break;
        }
        case SDLK_w:
        case SDLK_UP:
        {
            mYU = 1;
            break;
        }
        case SDLK_s:
        case SDLK_DOWN:
        {
            mYD = 1;
            break;
        }
        case SDLK_q:
        case SDLK_PAGEUP:
        {
            mZP = 1;
            break;
        }
        case SDLK_e:
        case SDLK_PAGEDOWN:
        {
            mZM = 1;
            break;
        }
        case SDLK_1:
        {
            currentTile = tileSolid;
            break;
        }
        case SDLK_2:
        {
            currentTile = tileWide;
            break;
        }
        case SDLK_3:
        {
            currentTile = tileHigh;
            break;
        }
        case SDLK_4:
        {
            currentTile = tileBig2x2;
            break;
        }
        case SDLK_5:
        {
            currentTile = tileDrop;
            break;
        }
        case SDLK_r:
        {
            if(resetTime == -1.0)
            {
                resetTime = 1.0;
            }
            break;
        }
        default:
        {
            break;
        }
    }
    if(interpolation == 0)
    {
        return;
    }
    switch(sym)
    {
        case SDLK_j:
        {
            rXL = 1;
            break;
        }
        case SDLK_l:
        {
            rXR = 1;
            break;
        }
        case SDLK_i:
        {
            rYD = 1;
            break;
        }
        case SDLK_k:
        {
            rYU = 1;
            break;
        }
        default:
        {
            break;
        }
    }
}

void CB_StateRoomTest::onKeyUp(SDL_Keycode sym, SDL_Keymod mod)
{
    switch(sym)
    {
        case SDLK_a:
        case SDLK_LEFT:
        {
            mXL = 0;
            break;
        }
        case SDLK_d:
        case SDLK_RIGHT:
        {
            mXR = 0;
            break;
        }
        case SDLK_w:
        case SDLK_UP:
        {
            mYU = 0;
            break;
        }
        case SDLK_s:
        case SDLK_DOWN:
        {
            mYD = 0;
            break;
        }
        case SDLK_q:
        case SDLK_PAGEUP:
        {
            mZP = 0;
            break;
        }
        case SDLK_e:
        case SDLK_PAGEDOWN:
        {
            mZM = 0;
            break;
        }
        default:
        {
            break;
        }
    }
    if(interpolation == 0)
    {
        return;
    }
    switch(sym)
    {
        case SDLK_j:
        {
            rXL = 0;
            break;
        }
        case SDLK_l:
        {
            rXR = 0;
            break;
        }
        case SDLK_i:
        {
            rYD = 0;
            break;
        }
        case SDLK_k:
        {
            rYU = 0;
            break;
        }
        default:
        {
            break;
        }
    }
}

void CB_StateRoomTest::onMouseMove(int mouseX, int mouseY, int relX, int relY, bool left, bool right, bool middle)
{
    xMouse = mouseX / CB_Screen::getScreenWidth() * CB_Screen::getWidth();
    yMouse = (CB_Screen::getScreenHeight() - mouseY) / CB_Screen::getScreenHeight() * CB_Screen::getHeight();
}

void CB_StateRoomTest::onLeftButtonUp(int mouseX, int mouseY)
{
    int32_t tX = mouseX / CB_Screen::getScreenWidth() * CB_Screen::getWidth();
    int32_t tY = (CB_Screen::getScreenHeight() - mouseY) / CB_Screen::getScreenHeight() * CB_Screen::getHeight();

    double w = CB_Screen::getWidth() / 2;
    double h = CB_Screen::getHeight() / 2;
    CB_Vector2D posVec = CB_Screen::getCameraToPlaneOnWorldZ(tX - w, tY - h, 0);
    tX = (posVec.x + room->getScreenLeft()) / 16;
    tY = (room->getScreenHeight() - posVec.y + room->getScreenTop()) / 16;
    if(room->isFree(tX, tY, currentTile) && tX > -1 && tX < (int32_t)room->getWidth() && tY > -1 && tY < (int32_t)room->getHeight())
    {
        room->addTile(tX, tY, currentTile);
        room->optimize(true);
        bounds = room->getBounds();
    }
}

void CB_StateRoomTest::onRightButtonUp(int mouseX, int mouseY)
{
    int32_t tX = mouseX / CB_Screen::getScreenWidth() * CB_Screen::getWidth();
    int32_t tY = (CB_Screen::getScreenHeight() - mouseY) / CB_Screen::getScreenHeight() * CB_Screen::getHeight();

    double w = CB_Screen::getWidth() / 2;
    double h = CB_Screen::getHeight() / 2;
    CB_Vector2D posVec = CB_Screen::getCameraToPlaneOnWorldZ(tX - w, tY - h, 0);
    tX = (posVec.x + room->getScreenLeft()) / 16;
    tY = (room->getScreenHeight() - posVec.y + room->getScreenTop()) / 16;
    if(tX > -1 && tX < (int32_t)room->getWidth() && tY > -1 && tY < (int32_t)room->getHeight() && room->getTileAt(tX, tY) != 0)
    {
        room->removeTile(tX, tY);
        room->optimize(true);
        bounds = room->getBounds();
    }
}
