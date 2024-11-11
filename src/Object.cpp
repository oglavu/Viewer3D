#include "Object.hpp"

void Object::addVertex(Point3f v) {
	m_vertecies.push_back(v);
}

void Object::addNormal(Point3f v) {
	m_normals.push_back(v);
}

void Object::addTexOffset(Point2f v) {
	m_textures.push_back(v);
}

void Object::addGroup(GroupPtr vM) {
	m_groups.push_back(vM);
}

std::ostream& operator<<(std::ostream& stream, Face& f) {
	stream << "Face: ";
	for (unsigned ix = 0; ix < f.m_vertexIndeces.size(); ix++) {
		stream << f.m_vertexIndeces[ix] << "/" << 
			f.m_normalIndeces[ix] << "/" << f.m_texCoordIndeces[ix] << " ";
	}

	return stream << "\n";
}

std::ostream& operator<<(std::ostream& stream, Group& g) {
	
	stream << "Group: \n----------\n";
	for (FacePtr e : g.m_faces) {
		stream << *e.get();
	}
	stream << *g.m_material.get();
	return stream << "\n";
}

std::ostream& operator<<(std::ostream& stream, Object& obj) {
	
	for (Point3f e : obj.m_vertecies) {
		stream << "Vertex: (" << e(0) << ", " << e(1) << ", " << e(2) << ")\n";
	}
	stream << "\n";

	for (Point3f e : obj.m_normals) {
		stream << "Normal: (" << e(0) << ", " << e(1) << ", " << e(2) << ")\n";
	}
	stream << "\n";

	for (Point2f e : obj.m_textures) {
		stream << "Texture: (" << e(0) << ", " << e(1) << ")\n";
	}

	for (GroupPtr e : obj.m_groups) {
		stream << *e.get() << "\n";
	}

	return stream << "\n";
}

Group::Group(MaterialPtr m): m_material(m) { }

void Group::addFace(FacePtr f) {
	m_faces.push_back(f);
}

MaterialPtr Group::getMaterial() const {
	return MaterialPtr();
}

Face::Face(MaterialPtr m): m_material(m) { }

void Face::addVertexIndex(unsigned u) {
	m_vertexIndeces.push_back(u);
}

void Face::addNormalIndex(unsigned u) {
	m_normalIndeces.push_back(u);
}

void Face::addTexCoordIndex(unsigned u) {
	m_texCoordIndeces.push_back(u);
}
