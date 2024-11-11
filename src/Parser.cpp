#include "Parser.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

ObjectPtr Parser::parseFile(const std::string fileName)
{
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
			group->addFace(Parser::parseFace(sstream, group->getMaterial()));
		} else if (syntaxType == "usemtl") {
			if (group.get() != nullptr)
				object->addGroup(group);
			sstream >> line;
			group.reset();
			group = Parser::parseGroup(line, materials);
		} else if (syntaxType == "mtllib") {
			sstream >> line;

			// TODO: iz std::vector prebaci u std::list ?
			std::vector<MaterialPtr>* tmp = Parser::parseMTL(line);
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
			material->setAmbientColor(p);
		}
		else if (syntaxType == "Kd") {
			sstream >> p[0] >> p[1] >> p[2];
			material->setDiffuseColor(p);
		}
		else if (syntaxType == "Ks") {
			sstream >> p[0] >> p[1] >> p[2];
			material->setSpecularColor(p);
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
			// texture
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

FacePtr Parser::parseFace(std::stringstream& sstream, MaterialPtr pM) {
	FacePtr pFace(new Face(pM));

	// vertex format: v/t/n
	// v: index of coord
	// t: [optional] index of tex offset
	// n: [optional] index of normal vector
	std::string vertex;

	while (!sstream.eof()) {
		sstream >> vertex;
		int params[3] = { 0, 0, 0 };

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
		
		pFace->addVertexIndex(params[0]);
		pFace->addTexCoordIndex(params[1]);
		pFace->addNormalIndex(params[2]);
	}

	return pFace;
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
