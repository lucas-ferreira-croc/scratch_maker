#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) 
{
	// get source from filepath
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	// ensure ifstream objects can throw exceptions

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{

		// open files
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);
		
		std::stringstream vertexShaderStream, fragmentShaderStream;

		// read file's buffer into streams
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "Error: Shader file not sucessfuly read" << std::endl;
	}


	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	Compile(vertexShaderCode, fragmentShaderCode);
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource) 
{
	unsigned int vertex, fragment;
	int sucess;
	char infoLog[512];

	int vertexCodeSize = strlen(vertexSource);
	int fragmentCodeSize = strlen(fragmentSource);

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, &vertexCodeSize);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Error compiling Vertex Shader: " << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, &fragmentCodeSize);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &sucess);
	if(!sucess)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Error compiling Fragment Shader: " << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	
	glGetProgramiv(ID, GL_LINK_STATUS, &sucess);
	if (!sucess) 
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Error linking the program: " << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::bind()
{
	glUseProgram(ID);
};


void Shader::setBool(const std::string& name, bool value) const 
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const 
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const 
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat3(const std::string& name, glm::mat3 value) const 
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const 
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}