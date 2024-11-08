#pragma once

#include "Object.hpp"

#include <string>
#include <sstream>


class Parser {
public:
	Parser() = delete;

	static Object* parseFile(const std::string fileName);

private:

	static Point3f parseVertex(std::stringstream&);
	static Point3f parseNormal(std::stringstream&);
	static Point2f parseTexOffset(std::stringstream&);

};

