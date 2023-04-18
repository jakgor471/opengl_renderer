#include "utils.h"

#include <fstream>

unsigned int readTextFile(const char* path, char*& buffer){
	std::ifstream file(path, std::ifstream::binary);
	unsigned int len = -1;

	if(file){
		file.seekg(0, file.end);
		len = file.tellg();
		file.seekg(0, file.beg);

		buffer = new char[len + 1];
		buffer[len] = '\0';

		file.read(buffer, len);
	}

	return len;
}

bool loadTexture(const char *path, Texture& tex){

}

unsigned int hashCstring(const char* p, unsigned int len) {
	unsigned int result = 0;
    const unsigned int prime = 31;
    for (unsigned int i = 0; i < len; ++i) {
        result = p[i] + (result * prime);
    }
    return result;
}

unsigned int hashCstring(const char* p) {
	unsigned int result = 0;
    const unsigned int prime = 31;
    for (unsigned int i = 0; p[i] != '\0'; ++i) {
        result = p[i] + (result * prime);
    }
    return result;
}
