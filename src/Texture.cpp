#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "GL/glew.h"
#include <iostream>

Texture::Texture(const std::string& path):
	m_path(path)
{
	// topleft -> botleft
	stbi_set_flip_vertically_on_load(1);

	unsigned char* local_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

	if (local_buffer == 0) {
		std::cout << "Texture (" << m_path << ") not loaded.\n";
		return;
	}
	
	glGenTextures(1, &m_tbo);
	glBindTexture(GL_TEXTURE_2D, m_tbo);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(local_buffer);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_tbo);
}

void Texture::bind(unsigned slot) const {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_tbo);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}