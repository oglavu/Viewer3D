#include "Object.hpp"

#include <GL/glew.h>

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

void Object::setShader(ShaderPtr s) {
	m_shader = s;
}

void Object::compile() {
	// only object knows its coords by value
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);

	unsigned count = m_vertecies.size();
	float* positions = new float[3 * count];

	for (unsigned ix = 0; ix < count; ix++) {
		positions[3 * ix + 0] = m_vertecies[ix](0);
		positions[3 * ix + 1] = m_vertecies[ix](1);
		positions[3 * ix + 2] = m_vertecies[ix](2);
	}

	glBufferData(GL_ARRAY_BUFFER, 3*count * sizeof(unsigned), positions, GL_DYNAMIC_DRAW);

	delete[] positions;
	
	for (unsigned i1 = 0; i1 < m_groups.size(); i1++) {
		GroupPtr group = m_groups[i1]; glGenBuffers(1, &group->m_id);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, group->m_id);

		for (unsigned i2 = 0; i2 < group->m_faces.size(); i2++) {
			FacePtr face = group->m_faces[i2];

			// all group has one or more faces (polygons)
			unsigned count = face->m_vertexIndeces.size();
			unsigned* indeces = new unsigned[count];

			for (unsigned ix = 0; ix < count; ix++) {
				indeces[ix] = face->m_vertexIndeces[ix];
			}
			
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), indeces, GL_DYNAMIC_DRAW);
			delete[] indeces;

		}
	}
}

void Object::render() {
	if (!m_shader.get())
		m_shader->use();

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);

	for (unsigned ix = 0; ix < m_groups.size(); ix++) {
		GroupPtr group = m_groups[ix];

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, group->m_id);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	}
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
