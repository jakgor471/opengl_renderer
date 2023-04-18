#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>

class Texture{
	unsigned int texId;
	unsigned short width;
	unsigned short height;
public:
	Texture();
	~Texture();
	void load(void* data, unsigned int format, unsigned int width, unsigned int height, int level);
	void bind();
};

#endif
