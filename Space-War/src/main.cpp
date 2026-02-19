// main.cpp

// 导入库文件
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <spdlog/spdlog.h>
#include <iostream>

// 全局变量
GLFWwindow* window;
int screenWidth, screenHeight;

// 纹理结构体
struct Texture {
	GLuint id;
	int width;
	int height;
};

// 定义多个纹理
Texture spaceshipTexture;
Texture spaceship2Texture;
Texture bulletTexture;
Texture bigBossTexture;
Texture starrySkyTexture;
Texture leftPortalTexture;
Texture rightPortalTexture;

// 窗口大小变化回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// 更新屏幕尺寸
	screenWidth = width;
	screenHeight = height;
	
	// 更新视口
	glViewport(0, 0, width, height);
	
	// 更新投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);
	
	// 重置模型视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// 初始化函数
bool init() {
	// 初始化GLFW
	if (!glfwInit()) {
		spdlog::error("Failed to initialize GLFW");
		return false;
	}
	// 使用立即模式
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	
	// 获取主显示器
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	if (!monitor) {
		spdlog::error("Failed to get primary monitor");
		glfwTerminate();
		return false;
	}
	
	// 获取显示器视频模式
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	if (!mode) {
		spdlog::error("Failed to get video mode");
		glfwTerminate();
		return false;
	}
	
	// 存储屏幕尺寸
	screenWidth = mode->width;
	screenHeight = mode->height;
	
	// 创建全屏窗口
	window = glfwCreateWindow(screenWidth, screenHeight, "Immediate Mode Image Display", monitor, NULL);
	if (!window) {
		spdlog::error("Failed to create window");
		glfwTerminate();
		return false;
	}
	
	// 设置当前上下文
	glfwMakeContextCurrent(window);
	
	// 注册窗口大小变化回调
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// 启用2D纹理
	glEnable(GL_TEXTURE_2D);
	
	// 启用混合模式（用于透明图片）
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// 设置视口
	glViewport(0, 0, screenWidth, screenHeight);
	
	// 设置投影矩阵为正交投影
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
	
	// 设置模型视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	return true;
}

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
	if (!loadTexture("./png/spaceship/spaceship.png", spaceshipTexture)) {glfwTerminate(); return -1;}
	if (!loadTexture("./png/spaceship_2/spaceship.png", spaceship2Texture)) {glfwTerminate(); return -1;}
	if (!loadTexture("./png/bullet/bullet.png", bulletTexture)) {glfwTerminate(); return -1;}
	if (!loadTexture("./png/big-boss/big-boss.png", bigBossTexture)) {glfwTerminate(); return -1;}
	if (!loadTexture("./png/starry-sky/starry-sky.png", starrySkyTexture)) {glfwTerminate(); return -1;}
	if (!loadTexture("./png/portal/left-portal.png", leftPortalTexture)) {glfwTerminate(); return -1;}
	if (!loadTexture("./png/portal/right-portal.png", rightPortalTexture)) {glfwTerminate(); return -1;}

	// 主循环
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// 处理事件
		glfwPollEvents();
		
		// 渲染所有纹理
		render(0, 0, 1.0f, starrySkyTexture);
		render(100, 100, 1.0f, spaceshipTexture);
		/*render(400, 100, 1.0f, spaceship2Texture);
		render(700, 100, 1.0f, bulletTexture);
		render(100, 300, 1.0f, bigBossTexture);
		render(400, 300, 1.0f, leftPortalTexture);
		render(700, 300, 1.0f, rightPortalTexture);*/
		
		// 交换缓冲区
		glfwSwapBuffers(window);
	}
	
	// 清理资源
	glDeleteTextures(1, &starrySkyTexture.id);
	glDeleteTextures(1, &spaceshipTexture.id);
	/*glDeleteTextures(1, &spaceship2Texture.id);
	glDeleteTextures(1, &bulletTexture.id);
	glDeleteTextures(1, &bigBossTexture.id);
	glDeleteTextures(1, &leftPortalTexture.id);
	glDeleteTextures(1, &rightPortalTexture.id);
	glfwTerminate();*/
	
	return 0;
}
