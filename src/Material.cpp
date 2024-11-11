#include "Material.hpp"
#include <iostream>

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

std::ostream& operator<<(std::ostream& stream, Material& m) {
	stream << "Material: \n----------\n";
	stream << "Ka: " << m.m_ambientColor(0) << " " << m.m_ambientColor(1) << " " << m.m_ambientColor(2) << '\n';
	stream << "Kd: " << m.m_diffuseColor(0) << " " << m.m_diffuseColor(1) << " " << m.m_diffuseColor(2) << '\n';
	stream << "Ks: " << m.m_specularColor(0) << " " << m.m_specularColor(1) << " " << m.m_specularColor(2) << '\n';
	stream << "Ns: " << m.m_specularFocus << "\n";
	stream << "Ni: " << m.m_opticalDensity << "\n";
	stream << "d: " << m.m_dissolveFactor << "\n";
	stream << "illum: " << m.m_illumination;

	return stream << "\n----------\n";
}
