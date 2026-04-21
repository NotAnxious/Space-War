// image.h

#ifndef IMAGE_H
#define IMAGE_H
#include <GLFW/glfw3.h>
#include "main.h"

// 纹理结构体
struct Texture {
	unsigned int id;
	int width;
	int height;
};

// 定义纹理变量
Texture starrySkyTexture;
Texture spaceShipTexture;
Texture eneTexture;
/*Texture bulletTexture;
Texture bigBossTexture;
Texture leftPortalTexture;
Texture rightPortalTexture;*/


// 加载图片为纹理
bool loadTexture(const char* imagePath, Texture& texture) {
	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);

	int width, height, channels;
	unsigned char* data = SOIL_load_image(imagePath, &width, &height, &channels, SOIL_LOAD_RGBA);

	// 加载失败
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
