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

	return stream << "\n";
}
