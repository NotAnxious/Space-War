// ship.h

#ifndef SHIP_H
#define SHIP_H
#include "main.h"

// 速度系数，控制飞船移动速度
const double shipSpeedFactor = 50.0; // 每秒移动的像素数
// 计算时间缩放因子
double shipTimeScale;
// 方向,true=左;false=右
bool dire = false;

int shipHealth = 100; // 飞船血量
double shipX = 960; // X坐标
double shipG = 0; // 速度


void SwitchInputMethod() {
	HWND hwnd = GetForegroundWindow();
	HKL englishHKL = LoadKeyboardLayout(L"00000409", KLF_ACTIVATE); // 切换输入法

	if (englishHKL) {
		PostMessage(hwnd, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)englishHKL);
		spdlog::info("Switched to US Keyboard (English)");
	}
	else {
		spdlog::error("Failed to load English keyboard layout");
	}
} 

long getRand(long randmin, long randmax) {
	return (rand() % (randmax - randmin + 1)) + randmin;
}
void RefreshShipPosit(double deltaTime) {
	// 计算时间缩放因子
	shipTimeScale = deltaTime * shipSpeedFactor;
	
	// 按键判断
	if (KEY_DOWN('A')) { dire = true; }
	if (KEY_DOWN('D')) { dire = false; }

	// 左右移动
	if (dire) {
		shipG -= 1 * shipTimeScale;
	}
	else if (!dire) {
		shipG += 1 * shipTimeScale;
	}
	// 应用速度到位置
	shipX += shipG * shipTimeScale;
}
#endif
