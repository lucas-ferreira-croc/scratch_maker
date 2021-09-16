#include "Buffer.h"

/////////////////////////// 
/// VertexBuffer
/////////////////////////// 

VertexBuffer::VertexBuffer(float* data, unsigned int size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &ID);
}

void VertexBuffer::unBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

/////////////////////////// 
/// IndexBuffer
/////////////////////////// 

IndexBuffer::IndexBuffer(unsigned int* data, unsigned int size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &ID);
}

void IndexBuffer::unBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

