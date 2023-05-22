#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funcao que cria um arquivo com base no nome dado e retorna o ponteiro para o arquivo
FILE *createFile(char *fileName);

// funcao que coloca no arquivo n bytes
void putBytes(FILE *file, char *bytes, int n);

// funcao que fecha o arquivo
void closeFile(FILE *file);

#endif