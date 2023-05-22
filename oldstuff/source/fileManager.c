#include "fileManager.h"

FILE *createFile(char *fileName)
{
    FILE *file = fopen(fileName, "w");
    return file;
}

void putBytes(FILE *file, char *bytes, int n)
{
    fwrite(bytes, sizeof(char), n, file);
}

void closeFile(FILE *file)
{
    fclose(file);
}