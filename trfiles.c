#include "trfiles.h"

FILE *openFile(char *fileName, int type)
{
    if(type == EXISTS)
    {
        FILE *file = fopen(fileName, "r");
        if(file == NULL)
        {
            printf("File %s does not exist\n", fileName);
            exit(1);
        }
        return file;
    }
    else if(type == CREATE)
    {
        FILE *file = fopen(fileName, "w");
        if(file == NULL)
        {
            printf("File %s could not be created\n", fileName);
            exit(1);
        }
        return file;
    }
}

void closeFile(FILE *file)
{
    fclose(file);
}

int getFileSize(FILE *file)
{
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    rewind(file);
    return size;
}

void writeFile(FILE *file, unsigned char *data, int n)
{
    fwrite(data, 1, n, file);
}

void copyFile(char *fileName, char *newFileName)
{
    FILE *file = openFile(fileName, EXISTS);
    FILE *newFile = openFile(newFileName, CREATE);

    int fileSize = getFileSize(file);
    int bytesRemaining = fileSize;
    int bytesToTransfer = 0;
    unsigned char *data = NULL;

    // Can only transfer 63 bytes or less at a time, do a for loop until file is copied
    while(bytesRemaining > 0)
    {
        if(bytesRemaining > 63)
        {
            bytesToTransfer = 63;
        }
        else
        {
            bytesToTransfer = bytesRemaining;
        }
        data = (unsigned char *) malloc(bytesToTransfer);
        // Use fread to fill data
        fread(data, 1, bytesToTransfer, file);
        // Use fwrite to write data
        fwrite(data, 1, bytesToTransfer, newFile);
        bytesRemaining -= bytesToTransfer;
    }
}