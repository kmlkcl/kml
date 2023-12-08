#include "smlkr_io.h"
#include <cstdio>
#include <cstdlib>

char* SMLKR_IO_ReadFileContent(const char* path)
{
    FILE* file = fopen(path, "r");
    if (!file)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(length + 1);
    if (!content)
    {
        fclose(file);
        return NULL;
    }

    fread(content, 1, length, file);
    fclose(file);

    content[length] = '\0';
    return content;
}