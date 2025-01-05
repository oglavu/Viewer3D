#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec2 texCoords;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, texCoords);
    FragColor = texColor;
}