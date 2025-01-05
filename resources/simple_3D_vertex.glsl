#version 330 core

// Input attributes
layout(location = 0) in vec3 aPosition; // Vertex position in object space
layout(location = 1) in vec3 aNormal;   // Vertex normal in object space
layout(location = 2) in vec2 aTexture;

// Uniforms
uniform mat4 view;       // View matrix
uniform mat4 projection; // Projection matrix
uniform vec3 light;   // Light position in world space

out vec4 vertexColor;

void main() {
    gl_Position = vec4(aPosition, 1.0);
    vertexColor = vec4(abs(aNormal.x), abs(aNormal.y), abs(aNormal.z), 1.0);
}
