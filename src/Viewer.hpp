#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Viewer {
private:

	glm::vec2 mousePosition;
	// nose up, nose left
	float m_pitch, m_yaw;
	// field of view
	float m_fov;
	// distance from m_center
	float m_distance;

	glm::vec3 m_position,
		m_front,
		m_right,
		m_top,
		m_center;

	static const float MOUSE_FACTOR;
	static const float SCROLL_FACTOR;

	static Viewer& getInstance();
public:

	static glm::mat4 getViewMatrix();

	static void cursorCallback(GLFWwindow*, double, double);
	static void scrollCallback(GLFWwindow*, double, double);

};

