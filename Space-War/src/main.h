#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <conio.h>
#include "rely\include\spdlog.h"
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <mmsystem.h>

long long score = 0;

//提升权限
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
		// 判断内存是否够用
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
void showImage(IMAGE* dstimg, int x, int y, IMAGE* srcimg) {
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER ,0,255,AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
bool pressTheEsaKey() {
	bool isPressed = (GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0; // Esc键
	if (isPressed) {
		spdlog::info("Escape key pressed, exiting game");
	}
	return isPressed;
}
bool pressTheDKey() {
	return (GetAsyncKeyState(0x44) & 0x8000) != 0; // D键
}

bool pressTheAKey() {
	return (GetAsyncKeyState(0X41) & 0x8000) != 0; // A键
}
#endif