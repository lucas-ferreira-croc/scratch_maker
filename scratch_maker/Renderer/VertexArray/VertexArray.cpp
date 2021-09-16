#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

void VertexArray::addVertexAttribPointer(unsigned int index, int size, int stride, int pointer)
{
	bind();
	if(!index)
	{
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)pointer);
	}
	else 
	{
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(pointer * sizeof(float)));
	}

	glEnableVertexAttribArray(index);
}

void VertexArray::bind()
{
	glBindVertexArray(ID);
}

void VertexArray::unBind()
{
	glBindVertexArray(0);
}
