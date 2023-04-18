#include "buffers.h"
#include <cstring>

#include "glutils.h"

Buffer::Buffer(unsigned int target){
	glGenBuffers(1, &bufferObj);
	count = 0;
	aligned = true;
	glTarget = target;
}

Buffer::~Buffer(){
	glDeleteBuffers(1, &bufferObj);
}

bool Buffer::load(void *data, unsigned int count, unsigned int size, unsigned int usage, bool aligned){
	glBindBuffer(glTarget, bufferObj);
	glBufferData(glTarget, size * count, data, usage);
	this->aligned = aligned;

	unsigned int trueSize;

	glGetBufferParameteriv(glTarget, GL_BUFFER_SIZE, (int*)(&trueSize));
	glBindBuffer(glTarget, 0);

	this->count = count;

	return trueSize == size * count;
}

void Buffer::layout(BlAttrib* attribs, unsigned int num){
	unsigned int pointer = 0;
	for(unsigned int i = 0; i < num; ++i){
		BlAttrib& cur = attribs[i];
		unsigned int size = sizeofGlEnum(cur.type);

		int x = pointer % size;

		pointer += ((size - x) * (int)(aligned && x > 0));
		cur.pointer = pointer;
		pointer += size * cur.size;
	}

	//pointer is a stride now
	glBindBuffer(glTarget, bufferObj);
	for(unsigned int i = 0; i < num; ++i){
		BlAttrib& cur = attribs[i];
		unsigned int location;

		if(cur.location > 0){
			location = cur.location - 1;
		} else if(!cur.location){
			location = i;
		} else{
			continue;
		}

		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, cur.size, cur.type, cur.normalized, pointer, (GLvoid*) cur.pointer);
	}
	glBindBuffer(glTarget, 0);
}

void Buffer::bind(){
	glBindBuffer(glTarget, bufferObj);
}

unsigned int Buffer::length(){
	return this->count;
}
