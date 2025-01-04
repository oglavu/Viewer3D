#include "Viewer.hpp"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

const float Viewer::MOUSE_FACTOR = 0.5f,
			Viewer::SCROLL_FACTOR = 1.0f;

Viewer::Viewer(glm::vec3 pos, float fov, float dist): 
	m_position(pos),
	m_fov(fov),
	m_distance(dist)
{ 
	m_front = { 0.0f, 0.0f, -1.0f },
	m_top = { 0.0f, 1.0f, 0.0f },
	m_right = { 1.0f, 0.0f, 0.0f },
	m_center = { 0.0f, 0.0f, 0.0f };
}

Viewer& Viewer::getInstance() {
	static Viewer v ({0, 0, 5}, 60.0f, 5.0f);
	return v;
}

float Viewer::getFov() {
	return glm::radians(Viewer::getInstance().m_fov);
}

glm::vec3 Viewer::getEye() {
	return glm::radians(Viewer::getInstance().m_position);
}

glm::mat4 Viewer::getViewMatrix() {
	Viewer& viewer = Viewer::getInstance();
	return glm::lookAt(viewer.m_position, viewer.m_position + viewer.m_front, viewer.m_top);
}

void Viewer::cursorCallback(GLFWwindow* window, double x, double y) {
	bool pressed = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);

	Viewer& viewer = Viewer::getInstance();

	if (!pressed) {
		viewer.mousePosition.x = x;
		viewer.mousePosition.y = y;
		return;
	}

	double dx = x - viewer.mousePosition.x,
		dy = y - viewer.mousePosition.y;

	viewer.m_yaw += dx * MOUSE_FACTOR;
	viewer.m_pitch -= dy * MOUSE_FACTOR;

	// narrow to [-90, 90] degs range
	viewer.m_pitch = std::max(std::min(viewer.m_pitch, 90.0f), -90.0f);

	std::cout << viewer.m_pitch << "\r";

	// recalculate frontmost and rightmost vertex
	float x_front = std::cos(glm::radians(viewer.m_yaw)) * std::cos(glm::radians(viewer.m_pitch));
	float y_front = std::sin(glm::radians(viewer.m_pitch));
	float z_front = std::sin(glm::radians(viewer.m_yaw)) * std::cos(glm::radians(viewer.m_pitch));

	viewer.m_front = glm::normalize(glm::vec3(x_front, y_front, z_front));
	viewer.m_right = glm::cross(viewer.m_front, viewer.m_top);
	viewer.m_position = viewer.m_center - viewer.m_front * viewer.m_distance;

	// position update

	viewer.mousePosition.x = x;
	viewer.mousePosition.y = y;

}

void Viewer::scrollCallback(GLFWwindow*, double x, double y) {
	// ignores x
	Viewer& viewer = Viewer::getInstance();

	viewer.m_distance -= y * Viewer::SCROLL_FACTOR;
	viewer.m_position = viewer.m_center - viewer.m_front * viewer.m_distance;

}
