#include "texture.h"

Texture::Texture(){
	glGenTextures(1, &texId);
	width = 0;
	height = 0;
}

Texture::~Texture(){
	glDeleteTextures(1, &texId);
}

void Texture::load(void* data, unsigned int format, unsigned int width, unsigned int height, int level){
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(){
	glBindTexture(GL_TEXTURE_2D, texId);
}
