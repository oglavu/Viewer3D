#pragma once

#include "Point3f.hpp"
#include "Material.hpp"
#include <vector>
#include <iostream>

class Face {
private:
	MaterialPtr m_material;

	std::vector<unsigned> m_vertexIndeces;
	std::vector<unsigned> m_normalIndeces;
	std::vector<unsigned> m_texCoordIndeces;

public:

	Face(MaterialPtr m);
	
	void addVertexIndex(unsigned);
	void addNormalIndex(unsigned);
	void addTexCoordIndex(unsigned);

	friend std::ostream& operator << (std::ostream&, Face& obj);

};

typedef std::shared_ptr<Face> FacePtr;

// surfaces in Object that have the same Material are grouped in Group
class Group {
private:
	MaterialPtr m_material;

	std::vector<FacePtr> m_faces;

public:

	Group(MaterialPtr m);
	void addFace(FacePtr f);

	MaterialPtr getMaterial() const;

	friend std::ostream& operator << (std::ostream&, Group& g);

};

typedef std::shared_ptr<Group> GroupPtr;

class Object {
private:
	std::vector<Point3f> m_vertecies;
	std::vector<Point3f> m_normals;
	std::vector<Point2f> m_textures;

	std::vector<GroupPtr> m_groups;

public:

	void addVertex(Point3f v);
	void addNormal(Point3f v);
	void addTexOffset(Point2f v);
	void addGroup(GroupPtr g);

	friend std::ostream& operator << (std::ostream&, Object& obj);

};

typedef std::shared_ptr<Object> ObjectPtr;


