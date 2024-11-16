#include "Viewer.hpp"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

const float Viewer::MOUSE_FACTOR = 1.0f,
			Viewer::SCROLL_FACTOR = 0.1f;

Viewer& Viewer::getInstance() {
	static Viewer v;
	return v;
}

glm::mat4 Viewer::getViewMatrix() {
	Viewer& viewer = Viewer::getInstance();
	return glm::lookAt(viewer.m_position, viewer.m_position + viewer.m_front, viewer.m_top);
}

void Viewer::cursorCallback(GLFWwindow* window, double x, double y) {
	bool pressed = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);

	Viewer& viewer = Viewer::getInstance();

	std::cout << "Mouse move: " << x << ' ' << y << " \r";

	if (!pressed) {
		viewer.mousePosition.x = x;
		viewer.mousePosition.y = y;
		return;
	}

	double dx = x - viewer.mousePosition.x,
		dy = y - viewer.mousePosition.y;

	viewer.m_yaw -= dx * MOUSE_FACTOR;
	viewer.m_pitch += dy * MOUSE_FACTOR;

	// narrow to [-90, 90] degs range
	float tmp = viewer.m_pitch;
	tmp = (tmp > 90.0f) ? 90.0f : ((tmp < -90.0f) ? -90.0f : tmp);
	viewer.m_pitch = tmp;

	// recalculate frontmost and rightmost vertex
	float x_front = std::cos(glm::radians(viewer.m_yaw)) * std::cos(glm::radians(viewer.m_pitch));
	float y_front = std::sin(glm::radians(viewer.m_pitch));
	float z_front = std::sin(glm::radians(viewer.m_yaw)) * std::cos(glm::radians(viewer.m_pitch));

	viewer.m_front = glm::normalize(glm::vec3(x_front, y_front, z_front));
	viewer.m_right = glm::cross(viewer.m_front, viewer.m_top);

	// position update

	viewer.mousePosition.x = x;
	viewer.mousePosition.y = y;

}

void Viewer::scrollCallback(GLFWwindow*, double x, double y) {
	// ignores x
	Viewer& viewer = Viewer::getInstance();

	std::cout << "Mouse scroll: " << y << " \r";

	viewer.m_fov -= y * Viewer::SCROLL_FACTOR;
	
	// narrow to [1, 80] degs range
	float tmp = viewer.m_fov;
	tmp = (tmp > 80.0f) ? 80.0f : ((tmp < 1.0f) ? 1.0f : tmp);
	viewer.m_fov = tmp;

	viewer.m_position = viewer.m_center - viewer.m_front * viewer.m_fov;

}
