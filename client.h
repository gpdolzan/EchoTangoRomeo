#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "md5.h"
#include "packet.h"

#define MD5_STRING 0
#define MD5_FILE 1

// Function that run client
void runClient();

// Function that receives a char and uses it as a command to run other functions
void receiveCommand(char command);

// Menu function command 1
void menuBackupSingleFile();

// Function that lists all files from current directory
void listFiles();

// Function that sends a file to server
void backupSingleFile(char* fileName);

// Function that changes current directory to the one specified by path
void changeDirectory(char* path);

// Function that calculates MD5 of a string or file
uint8_t* calculateMD5(char* data, int type);

// Function that frees memory of MD5 hash
void freeMD5(uint8_t* md5);

// Function that prints MD5 hash
void printMD5(uint8_t* md5);

#endif // __CLIENT_H__