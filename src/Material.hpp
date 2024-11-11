#pragma once

#include <string>
#include <memory>
#include "Point3f.hpp"

class Material {
private:
	std::string m_name;

	Point3f m_ambientColor;
	Point3f m_diffuseColor;
	Point3f m_specularColor;

	float m_specularFocus;
	float m_opticalDensity;
	float m_dissolveFactor;

	unsigned m_illumination;

public:
	explicit Material(std::string name);

	std::string getName() const;

	void setAmbientColor(Point3f v);
	void setDiffuseColor(Point3f v);
	void setSpecularColor(Point3f v);

	void setSpecularFocus(float f);
	void setOpticalDensity(float f);
	void setDissolveFactor(float f);

	void setIllumination(unsigned u);

	friend std::ostream& operator << (std::ostream&, Material&);

};

typedef std::shared_ptr<Material> MaterialPtr;