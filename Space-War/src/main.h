#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <conio.h>

// 定义GLFW_INCLUDE_NONE，这样GLFW就不会包含OpenGL的头文件，避免与glad.h冲突
#define GLFW_INCLUDE_NONE
#include "include\GLFW\glfw3.h"
#include "include\glm\glm.hpp"
#include "include\opencv2\opencv.hpp"
#include "include\SOIL2\SOIL2.h"
#include "include\spdlog\spdlog.h"
#include <vector>
#include <Windows.h>

long long score = 0;

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
extern Texture spaceshipTexture;
extern Texture spaceship2Texture;
extern Texture bulletTexture;
extern Texture bigBossTexture;
extern Texture starrySkyTexture;
extern Texture leftPortalTexture;
extern Texture rightPortalTexture;

// handle权限提升函数
bool EnablePrivileges(HANDLE hProcess, const WCHAR* pszPrivilegesName) {
	HANDLE hToken = NULL;
	LUID luidValue;
	TOKEN_PRIVILEGES tokenPrivileges;
	if (!OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken)) {
		spdlog::error("Unable to elevate privileges");
	}
	if (!LookupPrivilegeValue(NULL, pszPrivilegesName, &luidValue)) {
		CloseHandle(hToken);
		spdlog::error("Unable to elevate privileges");
	}
	tokenPrivileges.PrivilegeCount = 1;
	tokenPrivileges.Privileges[0].Luid = luidValue;
	tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, 0, NULL, NULL)) {
		CloseHandle(hToken);
		spdlog::error("Unable to elevate privileges");
	}
	CloseHandle(hToken);
	return GetLastError() == ERROR_SUCCESS;
}

// 获取系统内存使用情况
bool GetSystemMemoryUsage() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(memInfo);

	if (GlobalMemoryStatusEx(&memInfo)) {
		spdlog::info("Memory: {0}MB / {1}MB(%{2})", memInfo.ullTotalPhys / (1024 * 1024)
			, memInfo.ullAvailPhys / (1024 * 1024)
			, memInfo.dwMemoryLoad);
		return (memInfo.ullTotalPhys / (1024 * 1024) - memInfo.ullAvailPhys / (1024 * 1024) >= 19) ? true:false ;
	}
	else {
		spdlog::error("Unable to retrieve system memory information");
	}
}

// 获取CPU信息
void GetCpuInfo() {
	int cpuInfo[4] = { -1 };
	char cpuBrand[0x40] = { 0 };

	__cpuid(cpuInfo, 0x80000002);
	memcpy(cpuBrand, cpuInfo, sizeof(cpuInfo));
	__cpuid(cpuInfo, 0x80000003);
	memcpy(cpuBrand + 16, cpuInfo, sizeof(cpuInfo));
	__cpuid(cpuInfo, 0x80000004);
	memcpy(cpuBrand + 32, cpuInfo, sizeof(cpuInfo));

	spdlog::info("CPU:{}", cpuBrand);
}

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
	GetCpuInfo();
	EnablePrivileges(GetCurrentProcess(), SE_DEBUG_NAME);
	// 检查系统内存使用情况
	if (!GetSystemMemoryUsage()) {
		return false;
	}

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

#endif