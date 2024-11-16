#pragma once

#include <string>
#include <memory>

class Shader {
private:
	unsigned m_programId;
	enum ShaderType { VERTEX, FRAGMENT };

	static std::string readFile(std::string filePath);
	static unsigned compile(const char* str, ShaderType type);
	static unsigned link(const unsigned vertexId, const unsigned fragmentId);

public:
	Shader(std::string vsFileName, std::string fsFileName);

	void use() const;

};

typedef std::shared_ptr<Shader> ShaderPtr;