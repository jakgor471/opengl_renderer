#ifndef GLUTILS_H_
#define GLUTILS_H_

#include <GL/glew.h>

constexpr unsigned int sizeofGlEnum(GLenum glenum){
	switch(glenum){
	case GL_FLOAT:
		return sizeof(GLfloat);
	case GL_HALF_FLOAT:
		return sizeof(GLhalf);
	case GL_INT:
		return sizeof(GLint);
	case GL_UNSIGNED_INT:
		return sizeof(GLuint);
	case GL_BYTE:
		return sizeof(GLbyte);
	case GL_UNSIGNED_BYTE:
		return sizeof(GLubyte);
	case GL_SHORT:
		return sizeof(GLshort);
	case GL_UNSIGNED_SHORT:
		return sizeof(GLushort);
	case GL_FIXED:
		return sizeof(GLfixed);
	case GL_DOUBLE:
		return sizeof(GLdouble);
	case GL_FLOAT_VEC2:
		return sizeof(GLfloat) * 2;
	case GL_FLOAT_VEC3:
		return sizeof(GLfloat) * 3;
	case GL_FLOAT_VEC4:
		return sizeof(GLfloat) * 4;
	case GL_INT_VEC2:
		return sizeof(GLint) * 2;
	case GL_INT_VEC3:
		return sizeof(GLint) * 3;
	case GL_INT_VEC4:
		return sizeof(GLint) * 4;
	case GL_BOOL_VEC2:
		return sizeof(GLboolean) * 2;
	case GL_BOOL_VEC3:
		return sizeof(GLboolean) * 3;
	case GL_BOOL_VEC4:
		return sizeof(GLboolean) * 4;
	case GL_FLOAT_MAT2:
		return sizeof(GLfloat) * 4;
	case GL_FLOAT_MAT3:
		return sizeof(GLfloat) * 9;
	case GL_FLOAT_MAT4:
		return sizeof(GLfloat) * 16;
	case GL_FLOAT_MAT4x3:
		return sizeof(GLfloat) * 12;
	case GL_FLOAT_MAT4x2:
		return sizeof(GLfloat) * 8;
	case GL_FLOAT_MAT2x3:
		return sizeof(GLfloat) * 6;
	case GL_FLOAT_MAT2x4:
		return sizeof(GLfloat) * 8;
	case GL_FLOAT_MAT3x2:
		return sizeof(GLfloat) * 6;
	case GL_FLOAT_MAT3x4:
		return sizeof(GLfloat) * 12;
	default:
		return sizeof(GLint);
	}
}

#endif
