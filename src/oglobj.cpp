#ifndef _GLEW
#define _GLEW
#include <GL/glew.h>
#endif

struct RenderBlockListItem
{
	void* data;
	RenderBlockListItem* next;
};

class RenderBlock
{
	GLuint program;
	
	RenderBlockListItem* head;

public:
	RenderBlock() {
		program = 0;
		head = nullptr;
	}

	void Render() {
		glUseProgram()
	}
};

class OGLObject
{
	RenderBlock* pipeline;

	public:
	OGLObject() {
		pipeline = nullptr;
	}
};