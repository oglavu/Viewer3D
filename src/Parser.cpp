#include "Parser.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

Object* Parser::parseFile(const std::string fileName)
{
	Object* object = new Object();

	std::ifstream file (fileName);
	if (!file.is_open()) {
		throw new std::exception("Unable to open file");
	}
	std::string line;

	while (std::getline(file, line)) {
		std::string syntaxType;
		std::stringstream sstream(line);
		sstream >> syntaxType;

		if (syntaxType == "v") {
			object->addVertex(Parser::parseVertex(sstream));
		} else if (syntaxType == "vn") {
			object->addNormal(Parser::parseNormal(sstream));
		} else if (syntaxType == "vt") {
			object->addTexOffset(Parser::parseTexOffset(sstream));
		} else if (syntaxType == "f") {
			
		}
	}

	std::cout << line;
	return object;
}

Point3f Parser::parseVertex(std::stringstream& sstream) {
	float point[3];

	// breaks on whitespaces (newline, space...)
	sstream >> point[0] >> point[1] >> point[2];

	return Point3f(point);
}

Point3f Parser::parseNormal(std::stringstream& sstream) {
	float vector[3];

	// breaks on whitespaces (newline, space...)
	sstream >> vector[0] >> vector[1] >> vector[2];


	return Point3f(vector);
}

Point2f Parser::parseTexOffset(std::stringstream& sstream) {
	float texture[2] {0.0, 0.0};

	// breaks on whitespaces (newline, space...)
	sstream >> texture[0] >> texture[1];


	return Point2f(texture);
}
