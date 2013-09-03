#include "test/CB_StateTextureTest.h"
#include "CB_StateManager.h"

CB_StateTextureTest::CB_StateTextureTest()
{
    //ctor
}

CB_StateTextureTest::~CB_StateTextureTest()
{
    //dtor
}

void CB_StateTextureTest::start()
{
    theta = 0;
    minFov = 45;
    maxFov = 45;
    fov = 45;
    width = 320;
    height = 240;
    zNear = 0.5;
}

void CB_StateTextureTest::prerender()
{
    SDL_Surface * surface = SDL_LoadBMP("cb2.bmp");
    texture = CB_Texture::createTexture("cb", surface, GL_NEAREST, GL_NEAREST);
    SDL_FreeSurface(surface);
    surface = IMG_Load("testsheet.png");
    CB_Texture::createTexture("testsheet", surface, GL_NEAREST, GL_NEAREST);
    SDL_FreeSurface(surface);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -50000, 50000);
    glGetFloatv(GL_PROJECTION_MATRIX, orthoPMatrix);
    glPopMatrix();
}

void CB_StateTextureTest::stop()
{
}

void CB_StateTextureTest::run()
{
    theta+= 0.01;
    float ipol = sin(theta) / 2 + 0.5;
    fov = ipol * (maxFov - minFov) + minFov;
}

void CB_StateTextureTest::draw()
{
    float spol = (asin(sin(theta)) / PI + 0.5);
    spol = (spol * spol * spol);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    CB_Perspective(0, width, 0, height, fov, zNear, 50000);
    glGetFloatv(GL_PROJECTION_MATRIX, displPMatrix);
    for(uint32_t idx = 0; idx < 16; idx++)
    {
        displPMatrix[idx] = displPMatrix[idx] * spol + orthoPMatrix[idx] * (1.0 - spol);
    }
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    if(!CB_StateManager::isDeactivating())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(displPMatrix);

    // Data:
    // -30, 130, -10, 110 => -50, -50, 145);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    CB_Texture::bindTexture("testsheet");
    glTranslated(0, 0, -(0.5 * height / (tan(0.5 * fov * PI / 180))));

    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex3d(0, 0, 0);
        glTexCoord2i(1, 0); glVertex3d(100, 0, 0);
        glTexCoord2i(1, 1); glVertex3d(100, 100, 0);
        glTexCoord2i(0, 1); glVertex3d(0, 100, 0);
    glEnd();
    glPushMatrix();
    glTranslated(160, 120, -320);
    glRotated(500, 5, 3, 2);

    glBegin(GL_QUADS);
        glColor3d(0.5, 0.5, 1.0);
        glTexCoord2i(1, 1); glVertex3d(-40, 40, 40);
        glTexCoord2i(0, 1); glVertex3d(40, 40, 40);
        glTexCoord2i(0, 0); glVertex3d(40, 40, -40);
        glTexCoord2i(1, 0); glVertex3d(-40, 40, -40);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(0.5, 1.0, 0.5);
        glTexCoord2i(0, 0); glVertex3d(40, -40, -40);
        glTexCoord2i(1, 0); glVertex3d(40, -40, 40);
        glTexCoord2i(1, 1); glVertex3d(40, 40, 40);
        glTexCoord2i(0, 1); glVertex3d(40, 40, -40);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(1.0, 0.5, 0.5);
        glTexCoord2i(0, 0); glVertex3d(40, -40, -40);
        glTexCoord2i(1, 0); glVertex3d(-40, -40, -40);
        glTexCoord2i(1, 1); glVertex3d(-40, 40, -40);
        glTexCoord2i(0, 1); glVertex3d(40, 40, -40);
    glEnd();

    glTranslated(-80, 0, -80);

    glBegin(GL_QUADS);
        glColor3d(0.5, 0.5, 1.0);
        glTexCoord2i(1, 1); glVertex3d(-40, 40, 40);
        glTexCoord2i(0, 1); glVertex3d(40, 40, 40);
        glTexCoord2i(0, 0); glVertex3d(40, 40, -40);
        glTexCoord2i(1, 0); glVertex3d(-40, 40, -40);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(0.5, 1.0, 0.5);
        glTexCoord2i(0, 0); glVertex3d(40, -40, -40);
        glTexCoord2i(1, 0); glVertex3d(40, -40, 40);
        glTexCoord2i(1, 1); glVertex3d(40, 40, 40);
        glTexCoord2i(0, 1); glVertex3d(40, 40, -40);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(1.0, 0.5, 0.5);
        glTexCoord2i(0, 0); glVertex3d(40, -40, -40);
        glTexCoord2i(1, 0); glVertex3d(-40, -40, -40);
        glTexCoord2i(1, 1); glVertex3d(-40, 40, -40);
        glTexCoord2i(0, 1); glVertex3d(40, 40, -40);
    glEnd();

    glTranslated(80, -80, 0);

    glBegin(GL_QUADS);
        glColor3d(0.5, 0.5, 1.0);
        glTexCoord2i(1, 1); glVertex3d(-40, 40, 40);
        glTexCoord2i(0, 1); glVertex3d(40, 40, 40);
        glTexCoord2i(0, 0); glVertex3d(40, 40, -40);
        glTexCoord2i(1, 0); glVertex3d(-40, 40, -40);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(0.5, 1.0, 0.5);
        glTexCoord2i(0, 0); glVertex3d(40, -40, -40);
        glTexCoord2i(1, 0); glVertex3d(40, -40, 40);
        glTexCoord2i(1, 1); glVertex3d(40, 40, 40);
        glTexCoord2i(0, 1); glVertex3d(40, 40, -40);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(1.0, 0.5, 0.5);
        glTexCoord2i(0, 0); glVertex3d(40, -40, -40);
        glTexCoord2i(1, 0); glVertex3d(-40, -40, -40);
        glTexCoord2i(1, 1); glVertex3d(-40, 40, -40);
        glTexCoord2i(0, 1); glVertex3d(40, 40, -40);
    glEnd();

    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.6, 1.6, -1.2, 1.2, -1000, 1000);
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_LINES);
    glColor3d(1, 1, 1);
    glVertex2d(0, 0);
    glVertex2d(sin(theta), cos(theta));
    glEnd();
    glPopMatrix();
}
