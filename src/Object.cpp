#include "Object.hpp"

#include <GL/glew.h>

Object::Object() {
	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vao);
}

void Object::addVertex(glm::vec3 v) {
	m_vertecies.push_back(v);
}

void Object::addNormal(glm::vec3 v) {
	m_normals.push_back(v);
}

void Object::addTexOffset(glm::vec2 v) {
	m_texCoordOffs.push_back(v);
}

void Object::addGroup(GroupPtr vM) {
	m_groups.push_back(vM);
}

void Object::setShader(ShaderPtr s) {
	m_shader = s;
}

void Object::compile() {

	// -> Attribute [Bind]
	glBindVertexArray(m_vao);

	// -> Data
	unsigned count = m_vertecies.size();
	float* positions = new float[3 * count];

	for (unsigned ix = 0; ix < count; ix++) {
		positions[3 * ix + 0] = m_vertecies[ix].x;
		positions[3 * ix + 1] = m_vertecies[ix].y;
		positions[3 * ix + 2] = m_vertecies[ix].z;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * count * sizeof(float), positions, GL_STATIC_DRAW);
	delete[] positions;
	
	// -> Index
	for (unsigned i1 = 0; i1 < m_groups.size(); i1++) {
		GroupPtr group = m_groups[i1];

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, group->m_ebo);

		unsigned count = group->m_vertexIndeces.size();
		unsigned* indeces = group->m_vertexIndeces.data();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), indeces, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	// -> Attribute [Set]
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Object::render() {

	if (!m_shader.get())
		throw new std::runtime_error("No shader selected");
	m_shader->use();

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	for (unsigned ix = 0; ix < m_groups.size(); ix++) {
		GroupPtr group = m_groups[ix];

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, group->m_ebo);
		
		glDrawElements(GL_QUADS, group->m_vertexIndeces.size(), GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

std::ostream& operator<<(std::ostream& stream, Group& g) {
	
	stream << "Group: \n----------\n";
	for (unsigned ix = 0; ix < g.m_vertexIndeces.size(); ix++) {
		stream << g.m_vertexIndeces[ix] << "/" <<
			g.m_normalIndeces[ix] << "/" << g.m_texCoordIndeces[ix] << " ";
	}
	stream << "\n";
	stream << *g.m_material.get();
	return stream << "\n";
}

std::ostream& operator<<(std::ostream& stream, Object& obj) {
	
	for (glm::vec3 e : obj.m_vertecies) {
		stream << "Vertex: (" << e.x << ", " << e.y << ", " << e.z << ")\n";
	}
	stream << "\n";

	for (glm::vec3 e : obj.m_normals) {
		stream << "Normal: (" << e.x << ", " << e.y << ", " << e.z << ")\n";
	}
	stream << "\n";

	for (glm::vec2 e : obj.m_texCoordOffs) {
		stream << "Texture: (" << e.x << ", " << e.y << ")\n";
	}

	for (GroupPtr e : obj.m_groups) {
		stream << *e.get() << "\n";
	}

	return stream << "\n";
}

Group::Group(MaterialPtr m): m_material(m) {
	glGenBuffers(1, &m_ebo);
}

MaterialPtr Group::getMaterial() const {
	return MaterialPtr();
}

void Group::addVertexIndex(unsigned u) {
	m_vertexIndeces.push_back(u);
}

void Group::addNormalIndex(unsigned u) {
	m_normalIndeces.push_back(u);
}

void Group::addTexCoordIndex(unsigned u) {
	m_texCoordIndeces.push_back(u);
}
