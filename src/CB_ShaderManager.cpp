#include "CB_ShaderManager.h"

map<string,CB_Shader> CB_ShaderManager::programList;

CB_ShaderManager::CB_ShaderManager()
{
    //ctor
}

CB_ShaderManager::~CB_ShaderManager()
{
    //dtor
}

void CB_ShaderManager::addShader(string name)
{
    addShader(name, "shaders/" + name + ".vert", "shaders/" + name + ".frag");
}

void CB_ShaderManager::addShader(string name, string vertex, string fragment)
{
    GLint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    char * vFile = CB_FileLoader::loadText(vertex.c_str());
    char * fFile = CB_FileLoader::loadText(fragment.c_str());

    printf(vFile);

	const char * vChar = vFile;
	const char * fChar = fFile;

    glShaderSource(vShader, 1, &vChar, 0);
	glShaderSource(fShader, 1, &fChar, 0);

	GLint vCompiled = GL_FALSE;
	GLint fCompiled = GL_FALSE;

	free(vFile);
	free(fFile);

	glCompileShader(vShader);
	glCompileShader(fShader);

	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vCompiled);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fCompiled);

	CB_Shader shader;

	shader.program = glCreateProgram();
	if(vCompiled)
	{
	    glAttachShader(shader.program,vShader);
	}
	else
	{
	    fprintf(stderr, "Could not compile fragment vertex for program %s\n", name.c_str());
        GLint vLogLen = 0;
        glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &vLogLen);

        char * vLog = (char*)malloc(vLogLen);
        glGetShaderInfoLog(vShader, vLogLen, NULL, vLog);

        fprintf(stderr, "%s\n", vLog);

        free(vLog);
	}
	if(fCompiled)
	{
	    glAttachShader(shader.program,fShader);
	}
	else
	{
	    fprintf(stderr, "Could not compile fragment shader for program %s\n", name.c_str());
        GLint fLogLen = 0;
        glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &fLogLen);

        char * fLog = (char*)malloc(fLogLen);
        glGetShaderInfoLog(fShader, fLogLen, NULL, fLog);

        fprintf(stderr, "%s\n", fLog);

        free(fLog);
	}

	GLint pLink = GL_FALSE;

	glLinkProgram(shader.program);
	glGetProgramiv(shader.program, GL_LINK_STATUS, &pLink);
	if(!pLink)
	{
	    fprintf(stderr, "Could not link program %s\n", name.c_str());
        GLint pLogLen = 0;
        glGetProgramiv(shader.program, GL_INFO_LOG_LENGTH, &pLogLen);

        char * pLog = (char*)malloc(pLogLen);
        glGetProgramInfoLog(shader.program, pLogLen, NULL, pLog);

        fprintf(stderr, "%s\n", pLog);

        free(pLog);
	}

	programList[name] = shader;
}

CB_Shader CB_ShaderManager::getShader(string name)
{
    if(programList.count(name) == 0)
    {
        return CB_Shader();
    }
    return programList[name];
}

void CB_ShaderManager::useShader(string name)
{
    glUseProgram(getShader(name).program);
}

void CB_ShaderManager::addAttribute(string name, string attribName)
{
    if(programList.count(name) == 0)
    {
        return;
    }
    glLinkProgram(programList[name].program);
    programList[name].attribs[attribName] = glGetAttribLocation(programList[name].program, attribName.c_str());
}

GLint CB_ShaderManager::getAttribute(string name, string attribName)
{
    if(programList.count(name) == 0)
    {
        return -1;
    }
    if(programList[name].attribs.count(attribName) == 0)
    {
        addAttribute(name, attribName);
    }
    return programList[name].attribs[attribName];
}

void CB_ShaderManager::addUniform(string name, string unifName)
{
    if(programList.count(name) == 0)
    {
        return;
    }
    glLinkProgram(programList[name].program);
    programList[name].uniform[unifName] = glGetUniformLocation(programList[name].program, unifName.c_str());
}

GLint CB_ShaderManager::getUniform(string name, string unifName)
{
    if(programList.count(name) == 0)
    {
        return -1;
    }
    if(programList[name].uniform.count(unifName) == 0)
    {
        addUniform(name, unifName);
    }
    return programList[name].uniform[unifName];
}
