#pragma once

#include "Material.hpp"
#include "Shader.hpp"
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

// surfaces in Object that have the same Material are grouped in Group
class Group {
private:
	unsigned m_ebo;
	MaterialPtr m_material;

	std::vector<unsigned> m_vertexIndeces;
	std::vector<unsigned> m_normalIndeces;
	std::vector<unsigned> m_texCoordIndeces;

public:

	Group(MaterialPtr m);

	MaterialPtr getMaterial() const;

	void addVertexIndex(unsigned);
	void addNormalIndex(unsigned);
	void addTexCoordIndex(unsigned);

	friend class Object;
	friend std::ostream& operator << (std::ostream&, Group& g);

};

typedef std::shared_ptr<Group> GroupPtr;

class Object {
private:
	unsigned m_vbo, m_vao;

	std::vector<glm::vec3> m_vertecies;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_texCoordOffs;

	std::vector<GroupPtr> m_groups;

	ShaderPtr m_shader;

public:
	Object();

	void addVertex(glm::vec3);
	void addNormal(glm::vec3);
	void addTexOffset(glm::vec2);
	void addGroup(GroupPtr g);

	void setShader(ShaderPtr s);

	void compile();
	void render();

	friend std::ostream& operator << (std::ostream&, Object& obj);

};

typedef std::shared_ptr<Object> ObjectPtr;


