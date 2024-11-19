#pragma once

#include "Object.hpp"
#include "Material.hpp"

#include <string>
#include <sstream>
#include <glm/glm.hpp>


class Parser {
public:
	Parser() = delete;

	static ObjectPtr parseFile(const std::string fileName);

private:

	static std::vector<MaterialPtr>* parseMTL(const std::string fileName);

	static GroupPtr parseGroup(std::string, std::vector<MaterialPtr>&);
	static void parseFace(std::stringstream&, GroupPtr);

	static glm::vec3 parseVertex(std::stringstream&);
	static glm::vec3 parseNormal(std::stringstream&);
	static glm::vec2 parseTexOffset(std::stringstream&);

};

