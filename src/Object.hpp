#pragma once

#include "Point3f.hpp"
#include <vector>
#include <iostream>


class Object {
private:
	std::vector<Point3f> m_vertecies;
	std::vector<Point3f> m_normals;
	std::vector<Point2f> m_textures;


public:

	void addVertex(Point3f v);
	void addNormal(Point3f v);
	void addTexOffset(Point2f v);

	friend std::ostream& operator << (std::ostream&, Object& obj);


};

