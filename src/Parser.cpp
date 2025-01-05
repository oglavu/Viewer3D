#include "Parser.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

ObjectPtr Parser::parseFile(const std::string fileName) {
	ObjectPtr object(new Object());
	std::vector<MaterialPtr> materials;
	GroupPtr group(nullptr);

	std::ifstream file (fileName);
	if (!file.is_open()) {
		throw new std::runtime_error(std::string("Unable to open .obj file") + fileName);
	}
	std::string line;

	while (std::getline(file, line)) {
		std::string syntaxType;
		std::stringstream sstream(line);
		sstream >> syntaxType;

		if (syntaxType == "v") {
			object->addVertex(Parser::parseVertex(sstream));
		}
		else if (syntaxType == "vn") {
			object->addNormal(Parser::parseNormal(sstream));
		}
		else if (syntaxType == "vt") {
			object->addTexOffset(Parser::parseTexOffset(sstream));
		}
		else if (syntaxType == "f") {
			if (group.get() == nullptr)
				throw new std::runtime_error("Face definition before material specification");
			Parser::parseFace(sstream, group);
		} else if (syntaxType == "usemtl") {
			if (group.get() != nullptr)
				object->addGroup(group);
			sstream >> line;
			group.reset();
			group = Parser::parseGroup(line, materials);
		} else if (syntaxType == "mtllib") {
			sstream >> line;

			unsigned lastOccurence = fileName.find_last_of("/\\");
			if (lastOccurence == std::string::npos) {
				throw new std::runtime_error("Invalid path to .mtl file \n");
			}
			std::string path = fileName.substr(0, lastOccurence);
			std::vector<MaterialPtr>* tmp = Parser::parseMTL(path + std::string("/") + line);
			materials.insert(materials.begin(), tmp->begin(), tmp->end());
			delete tmp;
		}
	}

	if (group.get() != nullptr)
		object->addGroup(group);

	return object;
}

std::vector<MaterialPtr>* Parser::parseMTL(const std::string fileName) {
	std::vector<MaterialPtr>* materials = new std::vector<MaterialPtr>;
	MaterialPtr material(nullptr);

	std::ifstream file(fileName);
	if (!file.is_open()) {
		throw new std::runtime_error("Unable to open .mtl file");
	}

	float p[3];
	std::string line;
	std::string syntaxType;
	while (std::getline(file, line)) {
		std::stringstream sstream(line);
		sstream >> syntaxType;

		if (syntaxType == "Ka") {
			sstream >> p[0] >> p[1] >> p[2];
			material->setAmbientColor(glm::vec3(p[0], p[1], p[2]));
		}
		else if (syntaxType == "Kd") {
			sstream >> p[0] >> p[1] >> p[2];
			material->setDiffuseColor(glm::vec3(p[0], p[1], p[2]));
		}
		else if (syntaxType == "Ks") {
			sstream >> p[0] >> p[1] >> p[2];
			material->setSpecularColor(glm::vec3(p[0], p[1], p[2]));
		}
		else if (syntaxType == "Ns") {
			sstream >> p[0];
			material->setSpecularFocus(p[0]);
		}
		else if (syntaxType == "Ni") {
			sstream >> p[0];
			material->setOpticalDensity(p[0]);
		}
		else if (syntaxType == "d") {
			sstream >> p[0];
			material->setDissolveFactor(p[0]);
		}
		else if (syntaxType == "illum") {
			unsigned i; sstream >> i;
			material->setIllumination(i);
		}
		else if (syntaxType == "map_Kd") {
			sstream >> line;
			TexturePtr t(new Texture(line));
			material->addTexture(t);
		}
		else if (syntaxType == "newmtl") {
			sstream >> line;
			material = MaterialPtr(new Material(line));
			materials->push_back(material);
		}
	}

	return materials;

}

GroupPtr Parser::parseGroup(std::string materialName, std::vector<MaterialPtr>& materials) {
	GroupPtr group;

	for (MaterialPtr pMaterial : materials) {
		if (pMaterial.get()->getName() == materialName) {
			group.reset(new Group(pMaterial));
		}
	}

	if (group.get() == nullptr) {
		throw new std::runtime_error(std::string("No specified material: ") + materialName);
	}

	return group;
}

void Parser::parseFace(std::stringstream& sstream, GroupPtr g) {
	// parse and add to Group

	// vertex format: v/t/n
	// v: index of coord
	// t: [optional] index of tex offset
	// n: [optional] index of normal vector
	std::string vertex;

	unsigned vertexPerFace = 0;
	while (!sstream.eof()) {
		sstream >> vertex;
		unsigned params[3] = { 0, 0, 0 };
		vertexPerFace++;

		unsigned params_ix = 0;
		std::string num;
		for (unsigned ix = 0; ix < vertex.size(); ix++) {
			if (vertex[ix] == '/') {
				params[params_ix++] = std::stoi(num);
				num = "";
			} else {
				num += std::string(1, vertex[ix]);
			}				
		}
		params[params_ix] = std::stoi(num);
		
		g->addVertexIndex(params[0] - 1);
		g->addTexCoordIndex(params[1] - 1);
		g->addNormalIndex(params[2] - 1);
	}

	if (vertexPerFace > 4)
		throw new std::runtime_error("Too many vertecies per face provided.");
	if (vertexPerFace < 3)
		throw new std::runtime_error("Too little vertecies per face provided.");
}

glm::vec3 Parser::parseVertex(std::stringstream& sstream) {
	glm::vec3 vector;

	// breaks on whitespaces (newline, space...)
	sstream >> vector.x >> vector.y >> vector.z;

	return vector;
}

glm::vec3 Parser::parseNormal(std::stringstream& sstream) {
	glm::vec3 vector;

	// breaks on whitespaces (newline, space...)
	sstream >> vector.x >> vector.y >> vector.z;

	return vector;
}

glm::vec2 Parser::parseTexOffset(std::stringstream& sstream) {
	glm::vec2 vector;

	// breaks on whitespaces (newline, space...)
	sstream >> vector.x >> vector.y;

	return vector;
}
