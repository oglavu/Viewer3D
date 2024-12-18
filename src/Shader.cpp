#include "Shader.hpp"

#include <fstream>
#include <sstream>
#include <GL/glew.h>


std::string Shader::readFile(std::string filePath) {
	std::ifstream file(filePath);

	if (!file.is_open())
		throw new std::runtime_error(std::string("Couldnt open VertexShader file ") + filePath);

	std::stringstream stream;
	stream << file.rdbuf();

	return stream.str();
}

unsigned Shader::compile(const char* str, ShaderType type) {
	unsigned t = (type == VERTEX) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
	
	unsigned shaderId = glCreateShader(t);
	glShaderSource(shaderId, 1, &str, 0);
	glCompileShader(shaderId);

	int compilationStatus;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationStatus);

	if (compilationStatus != GL_TRUE) {
		int lenght;
		char msg[1024];
		glGetShaderInfoLog(shaderId, 1024, &lenght, msg);
		throw new std::runtime_error(msg);
	}

	return shaderId;
}

unsigned Shader::link(const unsigned vertexId, const unsigned fragmentId) {
	int pLinkingStatus;

	unsigned programId = glCreateProgram();
	glAttachShader(programId, vertexId);
	glAttachShader(programId, fragmentId);
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &pLinkingStatus);

	if (pLinkingStatus != GL_TRUE) {
		int lenght;
		char msg[1024];
		glGetProgramInfoLog(programId, 1024, &lenght, msg);
		throw new std::runtime_error(msg);
	}

	return programId;
}

Shader::Shader(std::string vsFileName, std::string fsFileName) {
	
	// -------- Read ------------
	std::string vsString = Shader::readFile(vsFileName);
	std::string fsString = Shader::readFile(fsFileName);

	const char const* vsChar = vsString.c_str();
	const char const* fsChar = fsString.c_str();

	// -------- Vertex ------------
	unsigned vertexId = Shader::compile(vsChar, VERTEX);

	// -------- Fragment ------------
	unsigned fragmentId = Shader::compile(fsChar, FRAGMENT);

	// -------- Linking ------------
	m_programId = Shader::link(vertexId, fragmentId);
}

void Shader::use() const {
	glUseProgram(m_programId);
}
