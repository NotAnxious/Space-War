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

//����Ȩ��
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
bool GetSystemMemoryUsage() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(memInfo);

	if (GlobalMemoryStatusEx(&memInfo)) {
		spdlog::info("Memory: {0}MB / {1}MB(%{2})", memInfo.ullTotalPhys / (1024 * 1024)
			, memInfo.ullAvailPhys / (1024 * 1024)
			, memInfo.dwMemoryLoad);
		// �ж��ڴ��Ƿ���
		return (memInfo.ullTotalPhys / (1024 * 1024) - memInfo.ullAvailPhys / (1024 * 1024) >= 19) ? true:false ;
	}
	else {
		spdlog::error("Unable to retrieve system memory information");
	}
}

// ��ȡCPU��Ϣ
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
#endif