#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec2 aTex;
  
out vec3 worldPos;
out vec3 normal;
out vec2 texCoords;

uniform mat4 model, view, projection;
uniform mat3 norm;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    worldPos = (model * vec4(aPos, 1.0)).xyz;
    normal = normalize(norm * aNor);
    texCoords = aTex;
}