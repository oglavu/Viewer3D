#pragma once

#include <string>
#include <memory>
#include <glm\glm.hpp>

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

	void uniform(const std::string, const glm::mat4& ) const;
	void uniform(const std::string, const glm::mat3& ) const;
	void uniform(const std::string, const glm::vec3& ) const;
	void uniform(const std::string, const glm::vec4& ) const;
	void uniform(const std::string, const int) const;
	void uniform(const std::string, const float) const;

};

typedef std::shared_ptr<Shader> ShaderPtr;