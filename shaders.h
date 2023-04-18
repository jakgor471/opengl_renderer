#ifndef SHADERS_H_
#define SHADERS_H_

#include <GL/glew.h>
#include <tuple>

#define SHDTYPE_VERTEX 0
#define SHDTYPE_FRAGMENT 1
#define SHD_NUM 2

struct Uniform{
	unsigned int type;
	unsigned int size;
	unsigned int location;
};

struct Attrib{
	unsigned int type;
	unsigned int size;
};

class GenericShader{
	std::tuple<unsigned int, const char*, Attrib> *attribs;
	std::tuple<unsigned int, const char*, Uniform> *uniforms;
	int numAttribs;
	int numUniforms;
	unsigned int shaders[SHD_NUM];
	unsigned int program;
	bool linked;

	int fetchUniforms();
	int fetchAttribs();
public:
	GenericShader();
	GenericShader(const char *vshdSource, const char *fshdSource);
	~GenericShader();

	void bindAttribute(int index, const char* name);
	void bind();
	bool addShaderSrc(const char *shdSrc, unsigned int shdtype);
	bool link();
	bool isLinked();
	bool getUniform(const char* name, Uniform& uniform);
	void setUniform(Uniform& uni, const void* data, int count);
	void setUniformMat(Uniform& uni, const void* data, bool transpose, int count);
	inline void setUniform(Uniform& uni, const void* data){
		setUniform(uni, data, 1);
	}
	inline void setUniformMat(Uniform& uni, const void* data, bool transpose){
		setUniformMat(uni, data, transpose, 1);
	}
};

#endif
