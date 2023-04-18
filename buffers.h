#ifndef BUFFERS_H_
#define BUFFERS_H_

#include <GL/glew.h>

class Buffer{
	unsigned int bufferObj;
	unsigned int glTarget;
	unsigned int count;
	bool aligned;
public:
	struct BlAttrib{
		unsigned int type;
		unsigned int pointer; //for later use
		int location;
		unsigned short size;
		GLboolean normalized; //GL_TRUE or GL_FALSE
	};

	Buffer(unsigned int target);
	~Buffer();

	bool load(void *data, unsigned int count, unsigned int size, unsigned int usage, bool aligned);
	void layout(BlAttrib* attribs, unsigned int num);
	void bind();
	unsigned int length();
};

#endif
