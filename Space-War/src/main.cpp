// main.cpp

// 导入库文件
#include "main.h"
#include "ship.h"
#include "image.h"
#include "ene.h"
#include <SOIL2/SOIL2.h>
#include <spdlog/spdlog.h>
#include <iostream>



// 主函数
int main() {
	// 初始化
	spdlog::info("Program starting...");
	if (!init()) {
		spdlog::error("Initialization failed!");
		spdlog::info("Press any key to exit...");
		_getch();
		return -1;
	}
	// 初始化随机种子
	srand((unsigned)time(NULL));

	// 初始化变量
	
	// 获取屏幕的实际宽度和高度
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	
	// 时间相关变量
	double lastTime = glfwGetTime();
	double deltaTime = 0.0;
	
	// FPS 相关变量
	int frameCount = 0;
	double fps = 0.0;
	double lastFpsUpdate = 0.0;
	
	// 敌方飞船生成计时器
	double lastEneSpawnTime = 0.0;
	
	
	
	// 欲加载所有纹理
	spdlog::info("Loading textures...");
	if (!loadTexture("./png/starry-sky/starry-sky.png", starrySkyTexture)) {
		spdlog::error("Failed to load starry-sky texture!");
		spdlog::info("Press any key to exit...");
		_getch();
		glfwTerminate();
		return -1;
	}
	spdlog::info("Starry sky texture loaded.");
	
	if (!loadTexture("./png/spaceship/spaceship.png", spaceShipTexture)) {
		spdlog::error("Failed to load spaceship texture!");
		spdlog::info("Press any key to exit...");
		_getch();
		glfwTerminate();
		return -1;
	}
	spdlog::info("Spaceship texture loaded.");
	
	if (!loadTexture("./png/spaceship_2/spaceship.png", eneTexture)) {
		spdlog::error("Failed to load enemy spaceship texture!");
		spdlog::info("Press any key to exit...");
		_getch();
		glfwTerminate();
		return -1;
	}
	spdlog::info("Enemy spaceship texture loaded.");
	
	spdlog::info("All textures loaded successfully!");
	
	// 注:前半部分均为初始化
	////////////////////////////////////////////////////////////////////////////////

	spdlog::info("Entering main loop...");

	// 主循环
	while (true) {
		// 计算deltaTime
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		
		// 计算FPS
		frameCount++;
		if (currentTime - lastFpsUpdate >= 1.0) {
			fps = frameCount / (currentTime - lastFpsUpdate);
			frameCount = 0;
			lastFpsUpdate = currentTime;
			spdlog::debug("FPS: {:.2f}", fps);
		}
		
		// 程序结束
		if (GetKeyState(VK_ESCAPE) & 0x8000 or glfwWindowShouldClose(window)) {
			glfwSetWindowShouldClose(window, true);
			// 清理资源
			glDeleteTextures(1, &starrySkyTexture.id);
			glDeleteTextures(1, &spaceShipTexture.id);
			glDeleteTextures(1, &eneTexture.id);
			glfwTerminate();
			return 0;
		}

		// 清屏
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 处理事件
		glfwPollEvents();
		
		// 渲染所有纹理
		render(0, 0, 1.0f, starrySkyTexture);
		showENE();
		render(shipX, 100, 1.0f, spaceShipTexture);

		// 更新坐标
		RefreshShipPosit(deltaTime);
		RefreshENEPosit(deltaTime);

		// 边界检查，防止飞船移出屏幕
		if (shipX > cx) shipX = 0;
		if (shipX < 0) shipX = cx;
		eneOutOfScreenDetection(cy);

		// 每秒有1/2概率生成敌方飞船
		if (currentTime - lastEneSpawnTime >= 1.0) {
			lastEneSpawnTime = currentTime;
			if (getRand(0, 1) == 0) { // 1/2概率
				addENE(getRand(0, cx), cy);
			}
		}

		// 交换缓冲区
		glfwSwapBuffers(window);
	}
	return 0;
}
