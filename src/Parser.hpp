#pragma once

#include "Object.hpp"
#include "Material.hpp"

#include <string>
#include <sstream>


class Parser {
public:
	Parser() = delete;

	static ObjectPtr parseFile(const std::string fileName);

private:

	static std::vector<MaterialPtr>* parseMTL(const std::string fileName);

	static GroupPtr parseGroup(std::string, std::vector<MaterialPtr>&);
	static FacePtr parseFace(std::stringstream&, MaterialPtr);

	static Point3f parseVertex(std::stringstream&);
	static Point3f parseNormal(std::stringstream&);
	static Point2f parseTexOffset(std::stringstream&);

};

