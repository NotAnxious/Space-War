// Texture.h

#ifndef TEXTURE_H
#define TEXTURE_H

#define GLFW_INCLUDE_NONE
#include "glad.h"
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <spdlog/spdlog.h>
#include <cstdlib>

struct Texture {
	unsigned int id;
	int width;
	int height;
};

inline bool loadTexture(const char* imagePath, Texture& texture) {
	// 设置环境变量来抑制 libpng 警告
	_putenv("PNG_SKIP_sRGB_CHECK=1");
	
	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);

	int width, height, channels;
	unsigned char* data = SOIL_load_image(imagePath, &width, &height, &channels, SOIL_LOAD_RGBA);

	if (!data) {
		spdlog::error("Failed to load image: {}", SOIL_last_result());
		return false;
	}

	texture.width = width;
	texture.height = height;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SOIL_free_image_data(data);

	return true;
}

#endif
