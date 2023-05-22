#ifndef __TRFILES_H__
#define __TRFILES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EXISTS 0
#define CREATE 1

// Function that opens a file with the given name and returns a pointer to it
FILE *openFile(char *fileName, int type);

// Function that closes a file
void closeFile(FILE *file);

// Function that gets file size in bytes
int getFileSize(FILE *file);

// Function that receives a string with name of a file and copies it to a new file
void copyFile(char *fileName, char *newFileName);

#endif // __TRFILES_H__