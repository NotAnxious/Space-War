#ifndef SHIP_H
#define SHIP_H
#include "main.h"

int shipHealth = 100;// 飞船血量
double shipX = 960;
double shipLG = 0; // 左加速度
double shipRG = 0; // 右加速度
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
void RefreshShipPosit() {
	// 丝滑移动
	if (pressTheAKey()) { shipLG = 30; }
	shipLG -= 1;
	if (pressTheDKey()) { shipRG = 30; }
	shipRG -= 1;
	// 确保加速度不为负数
	if (shipLG < 0) shipLG = 0;
	if (shipRG < 0) shipRG = 0;

	// 应用加速度到位置
	shipX += shipRG;
	shipX -= shipLG;
}
int returnShipX(){
	return shipX;
}
#endif