#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "utils.h"
#include "buffers.h"
#include "umath.h"
#include "objects.h"

#include "objgl2.h"
#include "shaders.h"

#if 1
int main(int argc, char * argv[])
{
	float x[5] = {0};
	float y[5];
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewInit();

	std::cout << "All systems on-line!\n";

	Buffer buffer(GL_ARRAY_BUFFER);
	Buffer indexbuffer(GL_ELEMENT_ARRAY_BUFFER);

	Buffer::BlAttrib attribs[3] = {
			{GL_FLOAT, 0, 1, 3, GL_FALSE},
			{GL_FLOAT, 0, -1, 2, GL_FALSE},
			{GL_FLOAT, 0, 2, 3, GL_FALSE}
	};

	buffer.layout(attribs, 3);

	char* rawobj;
	readTextFile("vokselia_spawn.obj", rawobj);

	const char *fname = "vokselia_spawn.obj";

	auto t1 = std::chrono::system_clock::now();
	//objgl2StreamInfo strinfo = objgl2_init_bufferstream(rawobj);
	unsigned int bufferSize = 65536;
	objgl2StreamInfo strinfo = objgl2_init_filestream((char*)fname, bufferSize);
	objgl2Data objd = objgl2_readobj(&strinfo);
	objgl2_deletestream(&strinfo);
	auto t2 = std::chrono::system_clock::now();

	buffer.load(objd.data, objd.numVertices, objd.vertSize, GL_STATIC_DRAW, true);
	indexbuffer.load(objd.indices, objd.numIndices, sizeof(unsigned int), GL_STATIC_DRAW, true);
	std::chrono::duration<double> diff = t2-t1;

	std::cout << "OBJ Loaded (" << diff.count() << "s): " << objd.numIndices << " indices, " << objd.numVertices << " vertices." << std::endl;

	objgl2_deleteobj(&objd);

	char* vshader = nullptr;
	char* fshader = nullptr;

	readTextFile("shaders/vshader.glsl", vshader);
	readTextFile("shaders/fshader.glsl", fshader);

	GenericShader shader;
	shader.addShaderSrc(vshader, SHDTYPE_VERTEX);
	shader.addShaderSrc(fshader, SHDTYPE_FRAGMENT);

	shader.link();

	Uniform uni_transform;
	Uniform uni_projection;
	Uniform uni_view;
	shader.getUniform("transform", uni_transform);
	shader.getUniform("projection", uni_projection);
	shader.getUniform("view", uni_view);

	umat4 projection = util_perspective(800.0 / 600, 70, 0.1f, 100);

	delete vshader;
	delete fshader;

	Camera camera;
	camera.setPos({0, 1, 2});

	Object obj;
	obj.setPos({0, 0, 0});

	shader.bind();
	shader.setUniformMat(uni_projection, (const void*)&projection, false);

	while(!glfwWindowShouldClose(window)){
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		buffer.bind();
		indexbuffer.bind();
		glDrawElements(GL_TRIANGLES, indexbuffer.length(), GL_UNSIGNED_INT, NULL);

		//camera.setAngle(camera.getAngle() + (uvec3){0, 0.1, 0});
		obj.setAngle(obj.getAngle() + (uvec3){0, 1, 0});
		shader.setUniformMat(uni_view, (const void*)camera.getViewMatrix(), false);
		shader.setUniformMat(uni_transform, (const void*)obj.getTransformMatrix(), false);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cout << "Terminated\n";

	return 0;
}
#else
int main(int argc, char * argv[]){
	char* rawobj;
	auto t1 = std::chrono::system_clock::now();
	readTextFile("tyra.obj", rawobj);

	unsigned long int pos = 0;
	objgl2StreamInfo stream;
	stream.buffer = rawobj;
	stream.buffOffset = 0;

	std::cout << sizeof(long int) << " " << sizeof(long long int) << std::endl;

	objgl2_readobj(objgl_bufferstreamreader, stream);

	//objgl2StreamInfo stream;
	//stream.fnameOrBuffer = rawobj;

	/*ObjGLData objd = objgl_loadObj(rawobj);
	auto t2 = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = t2-t1;

	std::cout << "time " << diff.count() << std::endl;

	t1 = std::chrono::system_clock::now();
	fastObjMesh* x = fast_obj_read("dragonmega.obj");
	t2 = std::chrono::system_clock::now();

	diff = t2-t1;

	std::cout << "time " << diff.count() << std::endl;*/

	return 0;
}
#endif
