#include "logger.h"
#include <cstring>
#include "utils.h"
#include "glutils.h"
#include "shaders.h"

GenericShader::GenericShader(){
	program = glCreateProgram();
	linked = false;

	for(unsigned int i = 0; i < SHD_NUM; ++i){
		shaders[i] = 0;
	}

	attribs = nullptr;
	uniforms = nullptr;
	numUniforms = 0;
	numAttribs = 0;
}

GenericShader::~GenericShader(){
	if(!linked){
		for(unsigned int i = 0; i < SHD_NUM; ++i){
			glDetachShader(program, shaders[i]);
			glDeleteShader(shaders[i]);
		}
	}

	glDeleteProgram(program);

	for(int i = 0; i < numAttribs; ++i){
		delete std::get<1>(attribs[i]);
	}

	for(int i = 0; i < numUniforms; ++i){
		delete std::get<1>(uniforms[i]);
	}

	delete uniforms;
	delete attribs;
}

int GenericShader::fetchUniforms(){
	if(linked) return 0;

	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &numUniforms);

	if(numUniforms > 0){
		uniforms = new std::tuple<unsigned int, const char*, Uniform>[numUniforms];

		for(int i = 0; i < numUniforms; ++i){
			char name[128];
			int len;
			unsigned int type;
			int size;
			glGetActiveUniform(program, i, 128, &len, &size, &type, name);

			char* n = new char[len + 1];
			n[len] = '\0';
			memmove((void*)n, (void*) name, len);

			Uniform uniform;
			uniform.type = type;
			uniform.size = size;
			uniform.location = glGetUniformLocation(program, name);

			uniforms[i] = std::tuple<unsigned int, const char*, Uniform>(hashCstring((const char*)n, (unsigned int)len), n, uniform);
		}
	}

	return numUniforms;
}

int GenericShader::fetchAttribs(){
	if(linked) return 0;

	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &numAttribs);

	if(numAttribs > 0){
		attribs = new std::tuple<unsigned int, const char*, Attrib>[numAttribs];

		for(int i = 0; i < numAttribs; ++i){
			char name[128];
			int len;
			unsigned int type;
			int size;
			glGetActiveAttrib(program, i, 128, &len, &size, &type, name);

			char* n = new char[len + 1];
			n[len] = '\0';
			memmove((void*)n, (void*) name, len);

			Attrib attrib;
			attrib.type = type;
			attrib.size = size;

			attribs[i] = std::tuple<unsigned int, const char*, Attrib>(hashCstring((const char*)n, (unsigned int)len), n, attrib);
		}
	}

	return numAttribs;
}

bool GenericShader::addShaderSrc(const char *shdSrc, unsigned int shdtype){
	const unsigned int mapping[SHD_NUM] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	unsigned int shd = glCreateShader(mapping[shdtype]);
	glShaderSource(shd, 1, &shdSrc, NULL);
	glCompileShader(shd);

	int status;
	glGetShaderiv(shd, GL_COMPILE_STATUS, &status);

	if(status != GL_TRUE){
		int len = 0;
		char msg[256];
		msg[0] = '\0';

		glGetShaderInfoLog(shd, 256, &len, msg);

		log(msg, LOGTYPE_ERROR);

		return false;
	}
	glAttachShader(program, shd);

	shaders[shdtype] = shd;

	return true;
}

bool GenericShader::link(){
	glLinkProgram(program);

	int status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if(status != GL_TRUE){
		int len = 0;
		char msg[256];
		msg[0] = '\0';

		glGetProgramInfoLog(program, 256, &len, msg);
		log(msg, LOGTYPE_ERROR);

		return false;
	}

	fetchAttribs();
	fetchUniforms();

	linked = true;

	for(unsigned int i = 0; i < SHD_NUM; ++i){
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	return true;
}

bool GenericShader::isLinked(){
	return linked;
}

void GenericShader::bindAttribute(int index, const char* name){
	glBindAttribLocation(program, index, name);
}

void GenericShader::bind(){
	glUseProgram(program);
}

bool GenericShader::getUniform(const char* name, Uniform& uniform){
	unsigned int hash = hashCstring(name);

	for(int i = 0; i < numUniforms; ++i){
		if(std::get<0>(uniforms[i]) == hash){
			uniform = std::get<2>(uniforms[i]);
			return true;
		}
	}

	return false;
}

void GenericShader::setUniform(Uniform& uni, const void* data, int count){
	switch(uni.type){
	case GL_FLOAT:
			glUniform1fv(uni.location, count, (const GLfloat*)data);
			break;
	case GL_FLOAT_VEC2:
			glUniform2fv(uni.location, count, (const GLfloat*)data);
			break;
	case GL_FLOAT_VEC3:
			glUniform3fv(uni.location, count, (const GLfloat*)data);
			break;
	case GL_FLOAT_VEC4:
			glUniform4fv(uni.location, count, (const GLfloat*)data);
			break;

	case GL_INT:
			glUniform1iv(uni.location, count, (const GLint*)data);
			break;
	case GL_INT_VEC2:
			glUniform2iv(uni.location, count, (const GLint*)data);
			break;
	case GL_INT_VEC3:
			glUniform3iv(uni.location, count, (const GLint*)data);
			break;
	case GL_INT_VEC4:
			glUniform4iv(uni.location, count, (const GLint*)data);
			break;

	case GL_BOOL:
			glUniform1iv(uni.location, count, (const GLint*)data);
			break;
	case GL_BOOL_VEC2:
			glUniform2iv(uni.location, count, (const GLint*)data);
			break;
	case GL_BOOL_VEC3:
			glUniform3iv(uni.location, count, (const GLint*)data);
			break;
	case GL_BOOL_VEC4:
			glUniform4iv(uni.location, count, (const GLint*)data);
			break;
	}
}

void GenericShader::setUniformMat(Uniform& uni, const void* data, bool transpose, int count){
	switch(uni.type){
	case GL_FLOAT_MAT4:
		glUniformMatrix4fv(uni.location, count, transpose, (const GLfloat*)data);
		break;
	case GL_FLOAT_MAT4x3:
		glUniformMatrix4x3fv(uni.location, count, transpose, (const GLfloat*)data);
		break;
	case GL_FLOAT_MAT4x2:
		glUniformMatrix4x2fv(uni.location, count,transpose,  (const GLfloat*)data);
		break;

	case GL_FLOAT_MAT3:
		glUniformMatrix3fv(uni.location, count, transpose, (const GLfloat*)data);
		break;
	case GL_FLOAT_MAT3x4:
		glUniformMatrix3x4fv(uni.location, count, transpose, (const GLfloat*)data);
		break;
	case GL_FLOAT_MAT3x2:
		glUniformMatrix3x2fv(uni.location, count, transpose, (const GLfloat*)data);
		break;

	case GL_FLOAT_MAT2:
		glUniformMatrix2fv(uni.location, count, transpose, (const GLfloat*)data);
		break;
	case GL_FLOAT_MAT2x4:
		glUniformMatrix2x4fv(uni.location, count, transpose, (const GLfloat*)data);
		break;
	case GL_FLOAT_MAT2x3:
		glUniformMatrix2x3fv(uni.location, count, transpose, (const GLfloat*)data);
		break;
	}
}
