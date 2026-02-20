// main.cpp

// 导入库文件
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include "main.h"

// 定义纹理变量
Texture starrySkyTexture;
Texture spaceShipTexture;
/*Texture spaceship2Texture;
Texture bulletTexture;
Texture bigBossTexture;
Texture leftPortalTexture;
Texture rightPortalTexture;*/


// 加载图片为纹理
bool loadTexture(const char* imagePath, Texture& texture) {
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

// 渲染函数
void render(int x, int y, float scale, const Texture& texture) {
	glBindTexture(GL_TEXTURE_2D, texture.id);
	
	float width = texture.width * scale;
	float height = texture.height * scale;
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(x, y);
	
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x + width, y);
	
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(x + width, y + height);
	
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x, y + height);
	glEnd();
}

// 主函数
int main() {

	// 初始化
	if (!init()) {
		return -1;
	}
	
	// 加载所有纹理
	if (!loadTexture("./png/starry-sky/starry-sky.png", starrySkyTexture)) { glfwTerminate(); return -1; }
	if (!loadTexture("./png/spaceship/spaceship.png", spaceShipTexture)) {glfwTerminate(); return -1;}
	/*if (!loadTexture("./png/spaceship_2/spaceship.png", spaceship2Texture)) { glfwTerminate(); return -1; }
	if (!loadTexture("./png/bullet/bullet.png", bulletTexture)) {glfwTerminate(); return -1;}
	if (!loadTexture("./png/big-boss/big-boss.png", bigBossTexture)) {glfwTerminate(); return -1;}
	if (!loadTexture("./png/portal/left-portal.png", leftPortalTexture)) {glfwTerminate(); return -1;}
	if (!loadTexture("./png/portal/right-portal.png", rightPortalTexture)) {glfwTerminate(); return -1;}*/

	// 主循环
	while (true) {
		// 程序结束
		if (GetKeyState(VK_ESCAPE) & 0x8000 or glfwWindowShouldClose(window)) {
			glfwSetWindowShouldClose(window, true);
			// 清理资源
			glDeleteTextures(1, &starrySkyTexture.id);
			glDeleteTextures(1, &spaceShipTexture.id);
			/*glDeleteTextures(1, &spaceship2Texture.id);
			glDeleteTextures(1, &bulletTexture.id);
			glDeleteTextures(1, &bigBossTexture.id);
			glDeleteTextures(1, &leftPortalTexture.id);
			glDeleteTextures(1, &rightPortalTexture.id);
			glfwTerminate();*/
			exit(0);
			return 0;
		}
		// 清屏
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// 处理事件
		glfwPollEvents();
		
		// 渲染所有纹理
		render(0, 0, 1.0f, starrySkyTexture);
		render(100, 100, 1.0f, spaceShipTexture);
		/*render(400, 100, 1.0f, spaceship2Texture);
		render(700, 100, 1.0f, bulletTexture);
		render(100, 300, 1.0f, bigBossTexture);
		render(400, 300, 1.0f, leftPortalTexture);
		render(700, 300, 1.0f, rightPortalTexture);*/
		
		// 交换缓冲区
		glfwSwapBuffers(window);
	}
	return 0;
}
