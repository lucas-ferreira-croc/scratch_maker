#pragma once

#include <glad/glad.h>
#include <glfw3.h>

class Buffer 
{
public:
	//virtual ~Buffer();

	virtual void unBind() const = 0;

	unsigned int getID() const { return ID; }
	
protected:
	unsigned int ID;
};

class VertexBuffer : public Buffer
{
public:
	VertexBuffer(float* data, unsigned int size);
	~VertexBuffer();

	void unBind() const override;

private:
};

class IndexBuffer : public Buffer
{
public:
	IndexBuffer(unsigned int* data, unsigned int size);
	~IndexBuffer();

	void unBind() const override;
private:
};