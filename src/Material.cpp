#include "Material.hpp"

Material::Material(std::string name): m_name(name){}

std::string Material::getName() const {
	return m_name;
}

void Material::setAmbientColor(Point3f v) {
	m_ambientColor = v;
}

void Material::setDiffuseColor(Point3f v) {
	m_diffuseColor = v;
}

void Material::setSpecularColor(Point3f v) {
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
