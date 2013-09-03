#include "test/CB_StateShaderTest.h"
#include "CB_StateManager.h"
#include "CB_Screen.h"

CB_StateShaderTest::CB_StateShaderTest()
{
    //ctor
}

CB_StateShaderTest::~CB_StateShaderTest()
{
    //dtor
}

void CB_StateShaderTest::start()
{

}

void CB_StateShaderTest::prerender()
{
    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);

    char * vs = CB_FileLoader::loadText("stateshadertest.vert");
    char * fs = CB_FileLoader::loadText("stateshadertest.frag");

    printf(vs);

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(v, 1, &vv, 0);
	glShaderSource(f, 1, &ff, 0);

	free(vs);
	free(fs);

	glCompileShader(v);
	glCompileShader(f);


	p = glCreateProgram();
	glAttachShader(p,v);
	glAttachShader(p,f);

	glLinkProgram(p);
}

void CB_StateShaderTest::run()
{

}

void CB_StateShaderTest::draw()
{
    if(!CB_StateManager::isDeactivating())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    CB_Screen::setSize(320, 240);
    CB_Screen::setProjection(1.0);
	glUseProgram(p);

    glColor3f(1.0, 1.0, 1.0);
    glTranslated(0.0, 0.0, -5.0);
	glBegin(GL_QUADS);
	glVertex2d(-0.5, -0.5);
	glVertex2d(0.0, -0.5);
	glVertex2d(0.0, 0.5);
	glVertex2d(-0.5, 0.5);
	glEnd();

	glUseProgram(0);

    glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2d(0.0, -0.5);
	glVertex2d(0.5, -0.5);
	glVertex2d(0.5, 0.5);
	glVertex2d(0.0, 0.5);
	glEnd();
}
