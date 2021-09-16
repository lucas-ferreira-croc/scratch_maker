#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader/Shader.h"

#include "VertexArray/VertexArray.h"
#include "Buffers/Buffer.h"

const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "scratch_maker", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	Shader shader("C:/croc/scratch_maker/scratch_maker/assets/shaders/vertex.glsl",
		"C:/croc/scratch_maker/scratch_maker/assets/shaders/fragment.glsl");

	float vertices[] = {
		//left posistions     //colors           //bottom posistions       
		-0.6f,  1.0f, 0.0f,   0.3f, 0.3f, 0.3f,   1.0f, -0.5f, 0.0f,  // upper right
		-0.6f, -1.0f, 0.0f,   0.3f, 0.3f, 0.3f,   1.0f, -1.0f, 0.0f,  // bottom right
		-1.0f, -1.0f, 0.0f,   0.3f, 0.3f, 0.3f,  -1.0f, -1.0f, 0.0f,  // bottom left
		-1.0f,  1.0f, 0.0f,   0.3f, 0.3f, 0.3f,  -1.0f, -0.5f, 0.0f   // upper left
	};

	unsigned int indices[] = {
		0, 1, 3, 
		1, 2, 3
	};

	// TODO = turn these unique_ptr objects into stack variables
	std::unique_ptr<VertexArray> vertexArray(new VertexArray());
	vertexArray->bind();

	std::unique_ptr<VertexBuffer> vertexBuffer(new VertexBuffer(vertices, sizeof(vertices)));;
	std::unique_ptr<IndexBuffer> indexBuffer(new IndexBuffer(indices, sizeof(indices)));

	// left position attribute
	vertexArray->addVertexAttribPointer(0, 3, 9, 0);

	// colour attribute
	vertexArray->addVertexAttribPointer(1, 3, 9, 3);

	// bottom position attribute
	vertexArray->addVertexAttribPointer(2, 3, 9, 6);

	vertexBuffer->unBind();
	vertexArray->unBind();

	while (!glfwWindowShouldClose(window)) 
	{
		// input
		processInput(window);

		// rendering
		shader.bind();

		shader.clearColor(0.3f, 0.3f, 1.0f, 0.0f);
		shader.clear();

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(-0.6f, 0.0f, 0.0f));
		transform = glm::scale(transform, glm::vec3(0.4f, 1.0f, 1.0f));
		shader.setMat4("transform", transform);
		vertexArray->bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		transform = glm::mat4(1.0f);
		transform = glm::rotate(transform, glm::radians(90.0f) , glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setMat4("transform", transform);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// swap buffers and events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shader.~Shader();

	glfwTerminate();
	return 0;
}