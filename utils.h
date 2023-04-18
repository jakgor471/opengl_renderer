#ifndef UTILS_H_
#define UTILS_H_

#include "texture.h"

unsigned int readTextFile(const char* path, char*& buffer);
bool loadTexture(const char *path, Texture& tex);
unsigned int hashCstring(const char* p, unsigned int len); //Credits: Aaditya Kalsi, Stack Overflow, thank you :)
unsigned int hashCstring(const char* p);

#endif
