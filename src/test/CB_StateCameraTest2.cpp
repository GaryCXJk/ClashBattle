#include "test/CB_StateCameraTest2.h"
#include "CB_StateManager.h"

CB_StateCameraTest2::CB_StateCameraTest2()
{
    //ctor
}

CB_StateCameraTest2::~CB_StateCameraTest2()
{
    //dtor
}

void CB_StateCameraTest2::start()
{
    speed = -1.0 / 30;
    interpolation = 0.0;
    theta = 0;
    tSpeed = 0;
    uint32_t camId = CB_Camera::createCamera();
    camera = CB_Camera::getCamera(camId);
    CB_Screen::setCamera(camId);
    CB_Screen::setSize(320, 240);
    CB_Screen::setFov(45);
    manualMode = false;
    x = 160;
    y = 120;
    z = 0;
    fLScale = 1.0;
    xRot = 0;
    yRot = 0;
    mXL = 0;
    mXR = 0;
    mYU = 0;
    mYD = 0;
    mZP = 0;
    mZM = 0;
    musicPlaying = false;
    beepPlaying = false;
    displayDebug = false;
    displayHelp = true;

    ticker = string(CB_FileLoader::loadText("testtext.txt"));

    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096);
    music = Mix_LoadMUS("mvwtheme.it");

    beepWave = CB_BEEPWAVE_SINE;
    beep = new CB_Beep();
    beep->setWave(440, beepWave);
}

void CB_StateCameraTest2::prerender()
{
    sheet = new CB_SpriteSheet();
    SDL_Surface * surface = IMG_Load("testsheet.png");
    CB_Texture::createTexture("sheet", surface, GL_NEAREST, GL_NEAREST);
    SDL_FreeSurface(surface);
    surface = IMG_Load("testfont.png");
    CB_Texture::createTexture("font", surface, GL_NEAREST, GL_NEAREST);
    SDL_FreeSurface(surface);
    surface = IMG_Load("plaid.png");
    map<GLenum, GLfloat> fMap;
    map<GLenum, GLint> iMap;
    iMap[GL_TEXTURE_MIN_FILTER] = GL_NEAREST;
    iMap[GL_TEXTURE_MAG_FILTER] = GL_NEAREST;
    iMap[GL_TEXTURE_WRAP_S] = GL_REPEAT;
    iMap[GL_TEXTURE_WRAP_T] = GL_REPEAT;
    CB_Texture::createTexture("plaid", surface, fMap, iMap);
    SDL_FreeSurface(surface);
    sheet->addTexture("sheet", CB_Texture::getTexture("sheet"));
    sheet->addFrame("regular", sheet->getTextureId("sheet"), 0, 0, 16, 16);
    sheet->addFrame("h_left", sheet->getTextureId("sheet"), 64, 0, 16, 16);
    sheet->addFrame("h_center", sheet->getTextureId("sheet"), 80, 0, 16, 16);
    sheet->addFrame("h_right", sheet->getTextureId("sheet"), 96, 0, 16, 16);
    sheet->addFrame("split_cross", sheet->getTextureId("sheet"), 80, 32, 16, 16);
    sheet->addFrame("circle", sheet->getTextureId("sheet"), 32, 48, 16, 16);
    sheet->addTexture("sheet", CB_Texture::getTexture("sheet"));

    CB_Font::createFont("testfont");
    font = CB_Font::getFont("testfont");
    font->addTexture("font", CB_Texture::getTexture("font"));
    font->setCharSpacing(1);
    font->setSpaceWidth(3);
    font->setNewLineHeight(9);
    font->addGlyph('A', font->getTextureId("font"), 0, 0, 7, 7, 7);
    font->addGlyph('B', font->getTextureId("font"), 8, 0, 7, 7, 7);
    font->addGlyph('C', font->getTextureId("font"), 16, 0, 7, 7, 7);
    font->addGlyph('D', font->getTextureId("font"), 24, 0, 7, 7, 7);
    font->addGlyph('E', font->getTextureId("font"), 32, 0, 7, 7, 7);
    font->addGlyph('F', font->getTextureId("font"), 40, 0, 7, 7, 7);
    font->addGlyph('G', font->getTextureId("font"), 48, 0, 7, 7, 7);
    font->addGlyph('H', font->getTextureId("font"), 56, 0, 7, 7, 7);
    font->addGlyph('I', font->getTextureId("font"), 65, 0, 5, 7, 7);
    font->addGlyph('J', font->getTextureId("font"), 72, 0, 7, 7, 7);
    font->addGlyph('K', font->getTextureId("font"), 80, 0, 7, 7, 7);
    font->addGlyph('L', font->getTextureId("font"), 88, 0, 7, 7, 7);
    font->addGlyph('M', font->getTextureId("font"), 96, 0, 7, 7, 7);
    font->addGlyph('N', font->getTextureId("font"), 104, 0, 7, 7, 7);
    font->addGlyph('O', font->getTextureId("font"), 112, 0, 7, 7, 7);
    font->addGlyph('P', font->getTextureId("font"), 120, 0, 7, 7, 7);
    font->addGlyph('Q', font->getTextureId("font"), 128, 0, 7, 7, 7);
    font->addGlyph('R', font->getTextureId("font"), 136, 0, 7, 7, 7);
    font->addGlyph('S', font->getTextureId("font"), 144, 0, 7, 7, 7);
    font->addGlyph('T', font->getTextureId("font"), 152, 0, 7, 7, 7);
    font->addGlyph('U', font->getTextureId("font"), 160, 0, 7, 7, 7);
    font->addGlyph('V', font->getTextureId("font"), 168, 0, 7, 7, 7);
    font->addGlyph('W', font->getTextureId("font"), 176, 0, 7, 7, 7);
    font->addGlyph('X', font->getTextureId("font"), 184, 0, 7, 7, 7);
    font->addGlyph('Y', font->getTextureId("font"), 192, 0, 7, 7, 7);
    font->addGlyph('Z', font->getTextureId("font"), 200, 0, 7, 7, 7);

    font->addGlyph('a', font->getTextureId("font"), 0, 9, 7, 6, 6);
    font->addGlyph('b', font->getTextureId("font"), 8, 8, 7, 7, 7);
    font->addGlyph('c', font->getTextureId("font"), 16, 9, 7, 6, 6);
    font->addGlyph('d', font->getTextureId("font"), 24, 8, 7, 7, 7);
    font->addGlyph('e', font->getTextureId("font"), 32, 8, 7, 7, 6);
    font->addGlyph('f', font->getTextureId("font"), 41, 8, 5, 7, 7);
    font->addGlyph('g', font->getTextureId("font"), 48, 8, 7, 8, 6);
    font->addGlyph('h', font->getTextureId("font"), 56, 8, 7, 7, 7);
    font->addGlyph('i', font->getTextureId("font"), 66, 8, 3, 7, 7);
    font->addGlyph('j', font->getTextureId("font"), 73, 8, 5, 8, 7);
    font->addGlyph('k', font->getTextureId("font"), 80, 8, 7, 7, 7);
    font->addGlyph('l', font->getTextureId("font"), 89, 8, 4, 7, 7);
    font->addGlyph('m', font->getTextureId("font"), 96, 9, 7, 6, 6);
    font->addGlyph('n', font->getTextureId("font"), 104, 9, 7, 6, 6);
    font->addGlyph('o', font->getTextureId("font"), 112, 9, 7, 6, 6);
    font->addGlyph('p', font->getTextureId("font"), 120, 8, 7, 7, 6);
    font->addGlyph('q', font->getTextureId("font"), 128, 8, 7, 7, 6);
    font->addGlyph('r', font->getTextureId("font"), 136, 9, 7, 6, 6);
    font->addGlyph('s', font->getTextureId("font"), 144, 8, 7, 7, 6);
    font->addGlyph('t', font->getTextureId("font"), 153, 8, 5, 7, 7);
    font->addGlyph('u', font->getTextureId("font"), 160, 9, 7, 6, 6);
    font->addGlyph('v', font->getTextureId("font"), 168, 9, 7, 6, 6);
    font->addGlyph('w', font->getTextureId("font"), 176, 9, 7, 6, 6);
    font->addGlyph('x', font->getTextureId("font"), 185, 9, 5, 6, 6);
    font->addGlyph('y', font->getTextureId("font"), 192, 8, 7, 7, 6);
    font->addGlyph('z', font->getTextureId("font"), 200, 9, 6, 6, 6);

    font->addGlyph('0', font->getTextureId("font"), 0, 16, 7, 7, 7);
    font->addGlyph('1', font->getTextureId("font"), 9, 16, 5, 7, 7);
    font->addGlyph('2', font->getTextureId("font"), 16, 16, 7, 7, 7);
    font->addGlyph('3', font->getTextureId("font"), 24, 16, 7, 7, 7);
    font->addGlyph('4', font->getTextureId("font"), 32, 16, 7, 7, 7);
    font->addGlyph('5', font->getTextureId("font"), 40, 16, 7, 7, 7);
    font->addGlyph('6', font->getTextureId("font"), 48, 16, 7, 7, 7);
    font->addGlyph('7', font->getTextureId("font"), 56, 16, 7, 7, 7);
    font->addGlyph('8', font->getTextureId("font"), 64, 16, 7, 7, 7);
    font->addGlyph('9', font->getTextureId("font"), 72, 16, 7, 7, 7);

    font->addGlyph(':', font->getTextureId("font"), 2, 25, 3, 5, 6);
    font->addGlyph('-', font->getTextureId("font"), 9, 26, 5, 3, 5);
    font->addGlyph('/', font->getTextureId("font"), 16, 24, 7, 7, 7);
    font->addGlyph('.', font->getTextureId("font"), 26, 28, 3, 3, 3);
    font->addGlyph(',', font->getTextureId("font"), 34, 27, 3, 4, 3);
    font->addGlyph('\'', font->getTextureId("font"), 34, 27, 3, 4, 7);
    font->addGlyph('"', font->getTextureId("font"), 34, 27, 5, 4, 7);
    font->addGlyph('_', font->getTextureId("font"), 40, 28, 7, 3, 2);
    font->addGlyph('#', font->getTextureId("font"), 48, 24, 7, 7, 7);
    font->addGlyph('!', font->getTextureId("font"), 58, 24, 3, 7, 7);

    tickerWidth = font->getStringWidth(ticker);

    tickerList = glGenLists(2);
    instructionList = tickerList + 1;
    glNewList(tickerList, GL_COMPILE);
    font->drawString(ticker, 124, 8);
    glEndList();
    glNewList(instructionList, GL_COMPILE);
    //    glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    font->drawString("USAGE:\n\nESCAPE - EXIT\nSPACE - SWITCH PROJECTION\nENTER - SWITCH ANIMATIONS\nTAB - SWITCH MANUAL MODE\nWASD / DIRECTIONAL KEYS - MOVE CAMERA\nLEFT MOUSE BUTTON - ROTATE CAMERA\nMOUSE WHEEL / Q E / PGUP PGDOWN - ZOOM IN / OUT\nR - RESET CAMERA\nM - TOGGLE MUSIC\nB - TOGGLE BEEP\nT - TOGGLE DEBUG\nH - TOGGLE HELP", -300, 200);
    glEndList();
    box = (CB_BoxRenderer*)CB_Renderer::getRenderer("box");
}

void CB_StateCameraTest2::stop()
{

}

void CB_StateCameraTest2::run()
{
    interpolation+= speed;
    interpolation = min(1.0f, max(0.0f, interpolation));
    theta+= 0.01 * tSpeed;
    x+= mXR - mXL;
    y+= mYU - mYD;
    fLScale+= 0.025 * (mZP - mZM);
    fLScale = max(0.025, fLScale);
    double iKey = 49.0 - (Uint16)(12.0 * (interpolation)) + 7 * (1 - cos(theta));
    beep->setWave(pow(2, (iKey - 49.0) / 12.0) * 440.0, beepWave);
}

void CB_StateCameraTest2::draw()
{
    float iPolRot = (-cos(interpolation * PI) / 2 + 0.5);

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    if(!CB_StateManager::isDeactivating())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    float autoFL = 1 / ((sin(theta * 1.5) * 0.5 + 1.0));
    float usedScale = 0;
    if(!manualMode)
    {
        CB_Screen::setOrthoZoom(autoFL);
        usedScale = autoFL;
    }
    else
    {
        CB_Screen::setOrthoZoom(fLScale);
        usedScale = fLScale;
    }
    CB_Screen::setProjection(interpolation);
    //CB_Screen::setOrthoZoom(1.0);
    if(!manualMode)
    {
        camera->setFocalLength(CB_Screen::getZ() * autoFL);
        camera->setPosition(160 + 64 * sin(theta), 120 + 64 * cos(theta), 0);
        camera->setRotation(sin(theta * 2) * 10 * iPolRot, cos(theta * 2) * 10 * iPolRot, 0);
    }
    else
    {
        camera->setFocalLength(CB_Screen::getZ() * fLScale);
        camera->setPosition(x, y, z);
        camera->setRotation(xRot * iPolRot, yRot * iPolRot, 0);
    }

    double zPosThing = CB_Screen::getZ();
    double fovThing = CB_Screen::getFOV();
    camera->doCamera();

    CB_Vector3D tVec(0, 0, camera->getFocalLength() - zPosThing);
    tVec = camera->getRotation() * tVec * tVec.length();
    tVec = tVec + camera->getPosition();
    CB_Vector3D dVec = camera->getActualPosition() - tVec;
    CB_Vector3D aVec = tVec - (dVec * (tVec.z / dVec.z));

    box->addBox(aVec.x, aVec.y, aVec.z, -1, -1, -1, 2, 2, 2, 0xFFFF0000, false);

    tVec = CB_Vector3D(64, 0, camera->getFocalLength() - zPosThing);
    tVec = camera->getRotation() * tVec * tVec.length();
    tVec = tVec + camera->getPosition();
    dVec = camera->getActualPosition() - tVec;
    aVec = tVec - (dVec * (tVec.z / dVec.z));

    box->addBox(aVec.x, aVec.y, aVec.z, -1, -1, -1, 2, 2, 2, 0xFFFF0000, false);

    tVec = CB_Vector3D(0, 64, camera->getFocalLength() - zPosThing);
    tVec = camera->getRotation() * tVec * tVec.length();
    tVec = tVec + camera->getPosition();
    dVec = camera->getActualPosition() - tVec;
    aVec = tVec - (dVec * (tVec.z / dVec.z));

    box->addBox(aVec.x, aVec.y, aVec.z, -1, -1, -1, 2, 2, 2, 0xFFFF0000, false);
    //glPushMatrix();
    //glTranslated(160 + 64 * sin(theta), 120 + 64 * cos(theta), 0);
    //drawBox(-4, -4, -4, 8, 8, 8);
    box->addBox(160 + 64 * sin(theta), 120 + 64 * cos(theta), 0, -4, -4, -4, 8, 8, 8, 0xFF5588FF, false);
    CB_Renderer::process();
    //glPopMatrix();

    //drawBox(80, 0, -1280, 320, 240, 80);
    //drawBox(128, 64, -24, 32, 16, 48);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    addLight(0.25, 0.5, 1, 0, 0xFF808080, 0xFFFFFFFF, GL_LIGHT0);
    box->addBox(80, 0, -1280, 0, 0, 0, 320, 240, 80, 0xFF8855FF, false);
    box->addBox(128, 64, -24, 0, 0, 0, 32, 16, 48, 0xFFFF5588, false);
    //drawBox(160, 0, -520, 320, 64, 400, 0xFF5599FF);
    box->addBox(160, 0, -520, 0, 0, 0, 160, 64, 200, 0xFF5599FF, false);
    box->addBox(320, 0, -520, 0, 0, 0, 160, 64, 200, 0xFF5599FF, true);
    box->addBox(160, 0, -320, 0, 0, 0, 160, 64, 200, 0xFF5599FF, true);
    box->addBox(320, 0, -320, 0, 0, 0, 160, 64, 200, 0xFF5599FF, false);
    CB_Renderer::process();
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    drawBox(448, 64, -520, 32, 32, 32);
    drawBox(0, 0, -120, 320, 32, 80);
    drawBox(0, 0, -400, 128, 144, 32);
    drawBox(0, 0, -40, 128, 128, 32);
    drawBox(0, 0, -8, 32, 16, 16);
    drawBox(32, 16, -8, 32, 16, 16);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    addLight(0, 0.25, 1, 0, 0xFF202020, 0xFFFFFFFF, 0xFFFFFFFF, GL_LIGHT0);
    glPushMatrix();
    glTranslated(64, 40, 0);
    glRotated(theta * 45, 1.0, 0.0, 0.0);
    string sA1[] = {"h_right", "split_cross", "regular", "h_left", "h_right", "h_left"};
    string sA2[] = {"h_center", "split_cross", "split_cross", "h_center", "h_center", "h_center"};
    string sA3[] = {"h_left", "regular", "split_cross", "h_right", "h_left", "h_right"};
    string sA4[] = {"regular", "regular", "regular", "regular", "regular", "regular"};
    drawBox(0, -8, -8, 16, 16, 16, sheet, sA1);
    drawBox(16, -8, -8, 16, 16, 16, sheet, sA2);
    //drawBox(32, -8, -8, 16, 16, 16, sheet, sA2);
    //drawBox(48, -8, -8, 16, 16, 16, sheet, sA3);
    box->addBox(40, 0, 0, -8, -8, -8, 16, 16, 16, sheet, sA2, true);
    box->addBox(56, 0, 0, -8, -8, -8, 16, 16, 16, sheet, sA3, true);
    box->addBox(72, 0, 0, -8, -8, -8, 16, 16, 16, sheet, sA4, true);
    box->addBox(88, 0, 0, -8, -8, -8, 16, 16, 16, 0xFFFFFFFF, true);
    CB_SpriteRenderer * sprite = (CB_SpriteRenderer*)CB_Renderer::getRenderer("sprite");
    sprite->addSprite(96, 8, 0, 0, 0, 0, sheet, "circle");
    CB_Renderer::process(64, 40, 0);
    glPopMatrix();
    CB_LineRenderer * lineRenderer = (CB_LineRenderer*)CB_Renderer::getRenderer("line");
    CB_SphereRenderer * sphereRenderer = (CB_SphereRenderer*)CB_Renderer::getRenderer("sphere");
    lineRenderer->addLine(120, 80, 0, -8, 0, 0, 8, 0, 0, 2);
    lineRenderer->addLine(120, 80, 0, 0, 0, 0, 0, 16, 0, 2);

    lineRenderer->addLine(136, 96, -8, -3, 0, 1, -1, 3, 1, 2, 0xFF0000FF);
    lineRenderer->addLine(136, 96, -8, -1, 3, 1, 0, 6, 0, 2, 0xFF0000FF);
    lineRenderer->addLine(136, 96, -8, 3, 0, -2, 3, 3.5, -2, 2, 0xFF0000FF);
    lineRenderer->addLine(136, 96, -8, 3, 3.5, -2, 0, 6, 0, 2, 0xFF0000FF);
    lineRenderer->addLine(136, 96, -8, 0, 6, 0, 0, 12, 0, 2, 0xFF0000FF);
    lineRenderer->addLine(136, 96, -8, 0, 12, 0, -2, 11, 3, 2, 0xFF0000FF);
    lineRenderer->addLine(136, 96, -8, -2, 11, 3, 1, 9, 4, 2, 0xFF0000FF);
    lineRenderer->addLine(136, 96, -8, 0, 12, 0, 3, 10, -2, 2, 0xFF0000FF);
    lineRenderer->addLine(136, 96, -8, 3, 10, -2, 6, 9, -2, 2, 0xFF0000FF);
    sphereRenderer->addSphere(136, 110, -8, 2, 32, 15, 0xFF0000FF, true);
    glDisable(GL_LIGHTING);
    CB_Renderer::process();
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
    drawBox(0, 80, -8, 16, 16, 8, sheet, sA4);
    glDisable(GL_TEXTURE_2D);
    sphereRenderer->addSphere(136, 128, -8, 2, 64, 31, 0xFF0000FF, true);
    //drawBox(96, 80, -8, 16, 16, 8, 0xFFFFFFFF);
    box->addBox(104, 88, -8, -8, -8, -8, 16, 16, 16, 0xFFFFFFFF, false);
    box->addBox(136, 88, -8, -8, -8, -8, 16, 16, 16, 0xFFFFFFFF, true);
    CB_Renderer::process();
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);
    glColorMask(0, 0, 0, 0);
    //glDisable(GL_DEPTH_TEST);
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    //drawBox(96, 80, -8, 16, 16, 8, 0xFFFFFFFF);
    box->addBox(104, 88, -8, -8, -8, -8, 16, 16, 16, 0xFFFFFFFF, false);
    box->addBox(136, 88, -8, -8, -8, -8, 16, 16, 16, 0xFFFFFFFF, true);
    CB_Renderer::process();
    glColorMask(1, 1, 1, 1);
    //glEnable(GL_DEPTH_TEST);
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glMatrixMode(GL_PROJECTION);
    float fTest[16];
    glGetFloatv(GL_PROJECTION_MATRIX, fTest);
    glLoadIdentity();
    CB_Screen::setOrthoZoom((manualMode ? fLScale : autoFL));
    CB_Screen::setOrtho();
    CB_Screen::setOrthoZoom(1.0);
    glMatrixMode(GL_MODELVIEW);
    float fTest2[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, fTest2);
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glDepthMask(false);

    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef((manualMode ? yRot : cos(theta * 2) * 10) * iPolRot * PI / 180, (manualMode ? xRot : sin(theta * 2) * 10) * iPolRot * PI / 180, 0);
    glMatrixMode(GL_MODELVIEW);
    glBlendFunc(GL_DST_COLOR, GL_ZERO);
    glEnable(GL_BLEND);
    CB_Texture::getTexture("plaid")->bind();
    glBegin(GL_QUADS);
    glTexCoord2d(0, 30);
    glVertex2d(-160, -120);
    glTexCoord2d(40, 30);
    glVertex2d(160, -120);
    glTexCoord2d(40, 0);
    glVertex2d(160, 120);
    glTexCoord2d(0, 0);
    glVertex2d(-160, 120);
    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glDepthMask(true);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(fTest);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_STENCIL_TEST);
    glLoadIdentity();
    glLoadMatrixf(fTest2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 144, -384);
    drawBox(0, 0, -4, 128, 4, 8, 0xFF808080);
    drawBox(0, 4, -4, 4, 16, 8, 0xFF808080);
    drawBox(124, 4, -4, 4, 16, 8, 0xFF808080);
    drawBox(0, 20, -4, 128, 4, 8, 0xFF808080);
    drawBox(4, 4, -4, 120, 16, 2, 0xFF808080);
    drawBox(4, 4, -2, 120, 16, 1.9, 0xFF000000);

    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);
    glColorMask(0, 0, 0, 0);
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glBegin(GL_QUADS);
    glVertex2d(4, 4);
    glVertex2d(124, 4);
    glVertex2d(124, 20);
    glVertex2d(4, 20);
    glEnd();
    glColorMask(1, 1, 1, 1);
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    double rTheta = theta * 100;
    uint32_t iTheta = (uint32_t)rTheta;
    rTheta = rTheta - iTheta;
    iTheta = iTheta % (tickerWidth + 248);
    rTheta+= iTheta;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(1.0, 1.0, 1.0);
    //font->drawString(ticker, 124 - rTheta, 8);
    glTranslated(-rTheta, 0.0, 0.0);
    glCallList(tickerList);
    glDisable(GL_BLEND);
    glDisable(GL_STENCIL_TEST);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glColor3d(1.0, 1.0, 1.0);
    /*glLineWidth(10 * (manualMode?1/fLScale:1/autoFL));
    glPointSize(10 * (manualMode?1/fLScale:1/autoFL));
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_POINTS);
    glVertex3d(-32, 128, -512);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(-32, 128, -512);
    glVertex3d(-32, 128, 0);
    glEnd();
    glBegin(GL_POINTS);
    glVertex3d(-32, 128, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(-32, 128, 0);
    glVertex3d(32, 128, 0);
    glEnd();
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glBegin(GL_POINTS);
    glVertex3d(32, 128, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(32, 128, 0);
    glVertex3d(32, 96, 0);
    glEnd();
    glBegin(GL_POINTS);
    glVertex3d(32, 96, 0);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POINT_SMOOTH);*/
    glLineWidth(1);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    camera->resetCamera();
    glPopMatrix();
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    CB_Screen::setOrthoZoom(2.0);
    CB_Screen::setOrtho();
    CB_Screen::setOrthoZoom(1.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4d(1.0, 1.0, 1.0, 1.0);
    if(displayHelp)
    {
        glCallList(instructionList);
    }
    //font->drawString((char*)glGetString(GL_EXTENSIONS), 0, 220);
    //font->drawString("ABCDEFGHIJKLM\nNOPQRSTUVWXYZ\nabcdefghijklm\nnopqrstuvwxyz", 0, 200);
    if(displayDebug)
    {
        for(int i = 0; i < 16; i++)
        {
            float cF = fTest[i];
            stringstream cvt;
            cvt << cF;
            double cFX = -300 + (i / 4) * 100;
            double cFY = 50 - (i % 4) * 10;
            font->drawString(cvt.str(), cFX, cFY);
        }
        for(int i = 0; i < 16; i++)
        {
            float cF = fTest2[i];
            stringstream cvt;
            cvt << cF;
            double cFX = -300 + (i / 4) * 100;
            double cFY = 0 - (i % 4) * 10;
            font->drawString(cvt.str(), cFX, cFY);
        }
        {
            stringstream cvt;
            cvt << zPosThing << " - " << fovThing;
            font->drawString(cvt.str(), -300, -50);
        }
    }
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
    glBegin(GL_LINES);
    glColor3d(1, 1, 1);
    glVertex2d(0, 0);
    glVertex2d(sin(interpolation * PI) * 100, cos(interpolation * PI) * 100);
    glEnd();
    glPopMatrix();
}

void CB_StateCameraTest2::onKeyDown(SDL_Keycode sym, SDL_Keymod mod)
{
    switch(sym)
    {
        case SDLK_SPACE:
        {
            speed = -speed;
            break;
        }
        case SDLK_RETURN:
        {
            tSpeed = 1 - tSpeed;
            break;
        }
        case SDLK_TAB:
        {
            manualMode = !manualMode;
            break;
        }
        case SDLK_ESCAPE:
        {
            SDL_Event event;
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);
            break;
        }
        case SDLK_m:
        {
            musicPlaying = !musicPlaying;
            if(musicPlaying)
            {
                Mix_PlayMusic(music, -1);
            }
            else
            {
                Mix_FadeOutMusic(500);
            }
            break;
        }
        case SDLK_b:
        {
            beepPlaying = !beepPlaying;
            if(beepPlaying)
            {
                Mix_PlayChannel(5, beep->getMixChunk(), -1);
            }
            else
            {
                Mix_HaltChannel(5);
            }
            break;
        }
        case SDLK_r:
        {
            x = 160;
            y = 120;
            z = 0;
            fLScale = 1.0;
            xRot = 0;
            yRot = 0;
            break;
        }
        case SDLK_t:
        {
            displayDebug = !displayDebug;
            break;
        }
        case SDLK_h:
        {
            displayHelp = !displayHelp;
            break;
        }
        default:
        {
            break;
        }
    }
    if(!manualMode)
    {
        return;
    }
    switch(sym)
    {
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
        default:
        {
            break;
        }
    }
}

void CB_StateCameraTest2::onKeyUp(SDL_Keycode sym, SDL_Keymod mod)
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
}

void CB_StateCameraTest2::onMouseMove(int mouseX, int mouseY, int relX, int relY, bool left, bool right, bool middle)
{
    if(!manualMode || interpolation == 0.0)
    {
        return;
    }
    if(left && right)
    {

    }
    if(left)
    {
        xRot+= relY * 0.5;
        yRot+= relX * 0.5;
    }
    if(right)
    {
        x-= relX;
        y+= relY;
    }
}

void CB_StateCameraTest2::onMouseWheel(bool up, bool down)
{
    if(!manualMode)
    {
        return;
    }
    if(up)
    {
        fLScale-= 0.025;
    }
    else
    {
        fLScale+= 0.025;
    }
    fLScale = max(0.25, fLScale);
}

void CB_StateCameraTest2::drawBox(double x, double y, double z, double w, double h, double d)
{
    glBegin(GL_QUADS);
        glColor3d(1.0, 0.0, 0.0);
        glVertex3d(x + w, y, z);
        glColor3d(0.0, 1.0, 0.0);
        glVertex3d(x, y, z);
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(x, y + h, z);
        glColor3d(0.0, 0.0, 1.0);
        glVertex3d(x + w, y + h, z);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(1.0, 0.0, 1.0);
        glVertex3d(x + w, y, z + d);
        glColor3d(1.0, 1.0, 0.0);
        glVertex3d(x + w, y, z);
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(x + w, y + h, z);
        glColor3d(0.0, 1.0, 1.0);
        glVertex3d(x + w, y + h, z + d);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(1.0, 0.0, 1.0);
        glVertex3d(x, y, z);
        glColor3d(1.0, 1.0, 0.0);
        glVertex3d(x, y, z + d);
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(x, y + h, z + d);
        glColor3d(0.0, 1.0, 1.0);
        glVertex3d(x, y + h, z);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(0.3, 0.5, 1.0);
        glVertex3d(x, y + h, z + d);
        glColor3d(1.0, 0.3, 0.5);
        glVertex3d(x + w, y + h, z + d);
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(x + w, y + h, z);
        glColor3d(0.5, 1.0, 0.3);
        glVertex3d(x, y + h, z);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(0.3, 0.5, 1.0);
        glVertex3d(x + w, y, z);
        glColor3d(1.0, 0.3, 0.5);
        glVertex3d(x, y, z);
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(x, y, z + d);
        glColor3d(0.5, 1.0, 0.3);
        glVertex3d(x + w, y, z + d);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(1.0, 0.0, 0.0);
        glVertex3d(x, y, z + d);
        glColor3d(0.0, 1.0, 0.0);
        glVertex3d(x + w, y, z + d);
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(x + w, y + h, z + d);
        glColor3d(0.0, 0.0, 1.0);
        glVertex3d(x, y + h, z + d);
    glEnd();
}

void CB_StateCameraTest2::drawBox(double x, double y, double z, double w, double h, double d, uint32_t color)
{
    GLfloat a = (float)((color >> 24) & 0xFF) / 255.0f;
    GLfloat r = (float)((color >> 16) & 0xFF) / 255.0f;
    GLfloat g = (float)((color >> 8) & 0xFF) / 255.0f;
    GLfloat b = (float)(color & 0xFF) / 255.0f;
    glColor4f(r, g, b, a);
    GLfloat matCol[] = {r, g, b, a};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matCol);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);
        glVertex3d(x + w, y, z);
        glVertex3d(x, y, z);
        glVertex3d(x, y + h, z);
        glVertex3d(x + w, y + h, z);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(1, 0, 0);
        glVertex3d(x + w, y, z + d);
        glVertex3d(x + w, y, z);
        glVertex3d(x + w, y + h, z);
        glVertex3d(x + w, y + h, z + d);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0);
        glVertex3d(x, y, z);
        glVertex3d(x, y, z + d);
        glVertex3d(x, y + h, z + d);
        glVertex3d(x, y + h, z);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3d(x, y + h, z + d);
        glVertex3d(x + w, y + h, z + d);
        glVertex3d(x + w, y + h, z);
        glVertex3d(x, y + h, z);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(0, -1, 0);
        glVertex3d(x + w, y, z);
        glVertex3d(x, y, z);
        glVertex3d(x, y, z + d);
        glVertex3d(x + w, y, z + d);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3d(x, y, z + d);
        glVertex3d(x + w, y, z + d);
        glVertex3d(x + w, y + h, z + d);
        glVertex3d(x, y + h, z + d);
    glEnd();
}

void CB_StateCameraTest2::drawBox(double x, double y, double z, double w, double h, double d, CB_SpriteSheet * spriteSheet)
{
    string sidesArray[] = {"back", "right", "left", "top", "bottom", "front"};
    string * sides = sidesArray;
    drawBox(x, y, z, w, h, d, spriteSheet, sides);
}

void CB_StateCameraTest2::drawBox(double x, double y, double z, double w, double h, double d, CB_SpriteSheet * spriteSheet, string * sides)
{
    double u1, v1, u2, v2;
    CB_Texture * tex;
    CB_SpriteFrame * frame;

    float verts[][4][3] = {
        { {x + w, y, z}, {x, y, z}, {x, y + h, z}, {x + w, y + h, z} },
        { {x + w, y, z + d}, {x + w, y, z}, {x + w, y + h, z}, {x + w, y + h, z + d} },
        { {x, y, z}, {x, y, z + d}, {x, y + h, z + d}, {x, y + h, z} },
        { {x, y + h, z + d}, {x + w, y + h, z + d}, {x + w, y + h, z}, {x, y + h, z} },
        { {x + w, y, z}, {x, y, z}, {x, y, z + d}, {x + w, y, z + d} },
        { {x, y, z + d}, {x + w, y, z + d}, {x + w, y + h, z + d}, {x, y + h, z + d} },
    };
    float normals[][3] = {
        {0, 0, -1},
        {1, 0, 0},
        {-1, 0, 0},
        {0, 1, 0},
        {0, -1, 0},
        {0, 0, 1},
    };

    glColor3f(1.0, 1.0, 1.0);

    for(int i = 0; i < 6; i++)
    {
        frame = spriteSheet->getFrame(sides[i]);
        tex = spriteSheet->getTexture(frame->texture);
        tex->bind();
        u1 = (frame->x) / (double)tex->getWidth();
        v1 = (frame->y) / (double)tex->getHeight();
        u2 = (frame->x + frame->width) / (double)tex->getWidth();
        v2 = (frame->y + frame->height) / (double)tex->getHeight();
        float ** pQuad;
        pQuad = new float*[4];
        for(int j = 0; j < 4; j++)
        {
            pQuad[j] = verts[i][j];
        }
        float * pN = normals[i];
        addQuad(pQuad, pN, u1, v1, u2, v2);
        delete[] pQuad;
    }
}

void CB_StateCameraTest2::addQuad(float ** verts, float * normals, double u1, double v1, double u2, double v2)
{
    glBegin(GL_QUADS);
        glNormal3f(normals[0], normals[1], normals[2]);
        glTexCoord2d(u1, v2);
        glVertex3d(verts[0][0], verts[0][1], verts[0][2]);
        glTexCoord2d(u2, v2);
        glVertex3d(verts[1][0], verts[1][1], verts[1][2]);
        glTexCoord2d(u2, v1);
        glVertex3d(verts[2][0], verts[2][1], verts[2][2]);
        glTexCoord2d(u1, v1);
        glVertex3d(verts[3][0], verts[3][1], verts[3][2]);
    glEnd();
}

void CB_StateCameraTest2::addLight(float x, float y, float z, float w, uint32_t ambient, uint32_t diffuse, GLenum light)
{
    GLfloat i, r, g, b;
    i = (float)((ambient >> 24) & 0xFF) / 255.0f;
    r = (float)((ambient >> 16) & 0xFF) / 255.0f;
    g = (float)((ambient >> 8) & 0xFF) / 255.0f;
    b = (float)(ambient & 0xFF) / 255.0f;
    GLfloat lightAmb[] = {r, g, b, i};
    i = (float)((diffuse >> 24) & 0xFF) / 255.0f;
    r = (float)((diffuse >> 16) & 0xFF) / 255.0f;
    g = (float)((diffuse >> 8) & 0xFF) / 255.0f;
    b = (float)(diffuse & 0xFF) / 255.0f;
    GLfloat lightDiff[] = {r, g, b, i};
    GLfloat lightPos[] = {x, y, z, w};
    glLightfv(light, GL_AMBIENT, lightAmb);
    glLightfv(light, GL_DIFFUSE, lightDiff);
    glLightfv(light, GL_POSITION, lightPos);
}

void CB_StateCameraTest2::addLight(float x, float y, float z, float w, uint32_t ambient, uint32_t diffuse, uint32_t specular, GLenum light)
{
    GLfloat i, r, g, b;
    i = (float)((ambient >> 24) & 0xFF) / 255.0f;
    r = (float)((ambient >> 16) & 0xFF) / 255.0f;
    g = (float)((ambient >> 8) & 0xFF) / 255.0f;
    b = (float)(ambient & 0xFF) / 255.0f;
    GLfloat lightAmb[] = {r, g, b, i};
    i = (float)((diffuse >> 24) & 0xFF) / 255.0f;
    r = (float)((diffuse >> 16) & 0xFF) / 255.0f;
    g = (float)((diffuse >> 8) & 0xFF) / 255.0f;
    b = (float)(diffuse & 0xFF) / 255.0f;
    GLfloat lightDiff[] = {r, g, b, i};
    i = (float)((specular >> 24) & 0xFF) / 255.0f;
    r = (float)((specular >> 16) & 0xFF) / 255.0f;
    g = (float)((specular >> 8) & 0xFF) / 255.0f;
    b = (float)(specular & 0xFF) / 255.0f;
    GLfloat lightSpec[] = {r, g, b, i};
    GLfloat lightPos[] = {x, y, z, w};
    glLightfv(light, GL_AMBIENT, lightAmb);
    glLightfv(light, GL_DIFFUSE, lightDiff);
    glLightfv(light, GL_SPECULAR, lightSpec);
    glLightfv(light, GL_POSITION, lightPos);
}
