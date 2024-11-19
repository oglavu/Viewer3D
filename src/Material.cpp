#include "Material.hpp"
#include <iostream>

Material::Material(std::string name): m_name(name){}

std::string Material::getName() const {
	return m_name;
}

void Material::setAmbientColor(glm::vec3 v) {
	m_ambientColor = v;
}

void Material::setDiffuseColor(glm::vec3 v) {
	m_diffuseColor = v;
}

void Material::setSpecularColor(glm::vec3 v) {
	m_specularColor = v;
}

void Material::setSpecularFocus(float f) {
	m_specularFocus = f;
}

void Material::setOpticalDensity(float f) {
	m_opticalDensity = f;
}

void Material::setDissolveFactor(float f) {
	m_dissolveFactor = f;
}

void Material::setIllumination(unsigned u) {
	m_illumination = u;
}

std::ostream& operator<<(std::ostream& stream, Material& m) {
	stream << "Material: \n----------\n";
	stream << "Ka: " << m.m_ambientColor.x << " " << m.m_ambientColor.y << " " << m.m_ambientColor.z << '\n';
	stream << "Kd: " << m.m_diffuseColor.x << " " << m.m_diffuseColor.y << " " << m.m_diffuseColor.z << '\n';
	stream << "Ks: " << m.m_specularColor.x << " " << m.m_specularColor.y << " " << m.m_specularColor.z << '\n';
	stream << "Ns: " << m.m_specularFocus << "\n";
	stream << "Ni: " << m.m_opticalDensity << "\n";
	stream << "d: " << m.m_dissolveFactor << "\n";
	stream << "illum: " << m.m_illumination;

	return stream << "\n----------\n";
}
