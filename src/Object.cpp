#include "Object.hpp"

#include <GL/glew.h>

Object::Object() {
	
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
	for (int i = 0; i < m_groups.size(); i++) {
		m_groups[i]->getMaterial()->setShader(s);
	}
}

void Object::compile() {

	// -> Attribute [Bind]
	glBindVertexArray(m_vao);

	// -> Data
	for (unsigned i1 = 0; i1 < m_groups.size(); i1++) {
		GroupPtr group = m_groups[i1];

		group->getMaterial()->use();

		glBindBuffer(GL_ARRAY_BUFFER, group->m_vbo);

		unsigned count = group->m_vertexIndeces.size();
		float* attributes = new float[8 * count];
		for (unsigned ix = 0; ix < count; ix++) {
			unsigned index = group->m_vertexIndeces[ix];
			attributes[8 * ix + 0] = m_vertecies[index].x;
			attributes[8 * ix + 1] = m_vertecies[index].y;
			attributes[8 * ix + 2] = m_vertecies[index].z;

			index = group->m_normalIndeces[ix];
			attributes[8 * ix + 3] = m_normals[index].x;
			attributes[8 * ix + 4] = m_normals[index].y;
			attributes[8 * ix + 5] = m_normals[index].z;

			index = group->m_texCoordIndeces[ix];
			attributes[8 * ix + 6] = m_texCoordOffs[index].x;
			attributes[8 * ix + 7] = m_texCoordOffs[index].y;
		}

		glBufferData(GL_ARRAY_BUFFER, 8 * count * sizeof(float), attributes, GL_STATIC_DRAW);

		// -> Attribute [Set]
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Object::draw() {

	if (!m_shader.get())
		throw new std::runtime_error("No shader selected");
	m_shader->use();

	glBindVertexArray(m_vao);

	for (unsigned ix = 0; ix < m_groups.size(); ix++) {
		GroupPtr group = m_groups[ix];

		glBindBuffer(GL_ARRAY_BUFFER, group->m_vbo);
		
		glDrawArrays(GL_QUADS, 0, group->m_vertexIndeces.size());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glBindVertexArray(0);

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
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
}

MaterialPtr Group::getMaterial() const {
	return m_material;
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
