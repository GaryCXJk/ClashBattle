#include "CB_FileLoader.h"

CB_FileLoader::CB_FileLoader()
{
    //ctor
}

CB_FileLoader::~CB_FileLoader()
{
    //dtor
}

char * CB_FileLoader::loadText(const char * fileName)
{
/*    FILE * file;
    char * content = 0;

    if(fileName == 0)
    {
        return 0;
    }

    file = fopen(fileName, "r");

    if(file == 0)
    {
        return 0;
    }

    fseek(file, 0, SEEK_END);
    size_t count = ftell(file);
    rewind(file);

    if(count > 0)
    {
        content = (char*)malloc(sizeof(char) * (count + 1));
        count = fread(content, sizeof(char), count, file);
        content[count] = '\0';
    }
    fclose(file);

    return content;*/

    CB_FileBinary bin = loadBinary(fileName);

    if(bin.length == 0)
    {
        return 0;
    }
    char * content = (char*)realloc(bin.data, bin.length + 1);
    content[bin.length] = '\0';

    return content;
}

CB_FileBinary CB_FileLoader::loadBinary(const char * fileName)
{
    FILE * file;
    uint8_t * content = 0;

    CB_FileBinary bin;

    if(fileName == 0)
    {
        return bin;
    }

    file = fopen(fileName, "r");

    if(file == 0)
    {
        return bin;
    }

    fseek(file, 0, SEEK_END);
    size_t count = ftell(file);
    rewind(file);

    if(count > 0)
    {
        content = (uint8_t*)malloc(sizeof(uint8_t) * count);
        count = fread(content, sizeof(uint8_t), count, file);
    }
    fclose(file);

    bin.length = count;
    bin.data = content;

    return bin;
}
