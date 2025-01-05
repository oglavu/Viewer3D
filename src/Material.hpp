#pragma once

#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Texture.h"

class Material {
private:
	std::string m_name;

	glm::vec3 m_ambientColor;
	glm::vec3 m_diffuseColor;
	glm::vec3 m_specularColor;

	float m_specularFocus;
	float m_opticalDensity;
	float m_dissolveFactor;

	unsigned m_illumination;

	ShaderPtr m_shader;
	std::vector<TexturePtr> m_textures;

public:
	explicit Material(std::string name);

	std::string getName() const;

	void addTexture(TexturePtr);

	void setAmbientColor(glm::vec3 v);
	void setDiffuseColor(glm::vec3 v);
	void setSpecularColor(glm::vec3 v);

	void setSpecularFocus(float f);
	void setOpticalDensity(float f);
	void setDissolveFactor(float f);

	void setIllumination(unsigned u);

	void setShader(ShaderPtr);

	void use() const;

	friend std::ostream& operator << (std::ostream&, Material&);

};

typedef std::shared_ptr<Material> MaterialPtr;