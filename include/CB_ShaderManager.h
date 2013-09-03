#ifndef CB_SHADERMANAGER_H
#define CB_SHADERMANAGER_H
#include "ClashBattle.h"
#include "CB_FileLoader.h"

struct CB_Shader
{
    GLuint program;
    map<string,GLint> attribs;
    map<string,GLint> uniform;
    CB_Shader()
    {
        program = 0;
    }
};

class CB_ShaderManager
{
    public:
        CB_ShaderManager();
        virtual ~CB_ShaderManager();
        static void addShader(string name);
        static void addShader(string name, string vertex, string fragment);
        static CB_Shader getShader(string name);
        static void useShader(string name);
        static void addAttribute(string name, string attribName);
        static GLint getAttribute(string name, string attribName);
        static void addUniform(string name, string unifName);
        static GLint getUniform(string name, string unifName);
    protected:
    private:
        static map<string,CB_Shader> programList;
};

#endif // CB_SHADERMANAGER_H
