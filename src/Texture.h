#pragma once

#include "memory"
#include "string"

class Texture {
private:
	unsigned m_tbo;
	std::string m_path;
	int m_width, m_height, m_bpp;

public:
	Texture(const std::string& path);

	~Texture();
	
	void bind(unsigned slot = 0) const;
	void unbind() const;

	unsigned get_height() const { return m_width; }
	unsigned get_width() const { return m_height; }

};

typedef std::shared_ptr<Texture> TexturePtr;
