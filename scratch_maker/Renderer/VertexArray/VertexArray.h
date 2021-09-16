#pragma once

#include <glad/glad.h>
#include <glfw3.h>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void addVertexAttribPointer(unsigned int index, int size, int stride, int pointer);

	void bind();
	void unBind();

	unsigned int getID() const { return ID; }

private:
	unsigned int ID;
};
