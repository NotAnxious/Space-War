#ifndef BULLET_H
#define BULLET_H

#include "main.h"
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
IMAGE bulletPng;
vector<int> bulletX;
vector<int> bulletY;
// 碰撞箱常量（便于调整与统一管理）
static const int ENE_W = 400;
static const int ENE_HIGH = 242;
static const int BULLET_W = 64;
static const int BULLET_HIGH = 322;

void createbullet(int x, int y) {
	if (KEY_DOWN(VK_LBUTTON)) {
		bulletX.push_back(x);
		bulletY.push_back(y - 322);
	}
}
void RefreshBulletPosit() {
	for (int i = 0; i < bulletY.size(); ++i) {
		bulletY[i] -= 5.0;
	}
}
void bulletOutOfScreenDetection() {
	for (int i = static_cast<int>(bulletY.size()) - 1; i >= 0; --i) {
		if (bulletY[i] <= -322) {
			// 从末尾向前遍历并删除越界的子弹，避免索引失效与越界访问
			bulletY.erase(bulletY.begin() + i);
			bulletX.erase(bulletX.begin() + i);
		}
	}
}
void collisionDetection() {

	// 从后向前遍历，删除元素时不会影响尚未处理的索引，避免越界
	for (int c = static_cast<int>(eneY.size()) - 1; c >= 0; --c) {
		for (int b = static_cast<int>(bulletY.size()) - 1; b >= 0; --b) {
			int bx = bulletX[b];
			int by = bulletY[b];
			int ex = eneX[c];
			int ey = eneY[c];

			// AABB 碰撞检测
			if (bx < (ex + ENE_W) && (bx + BULLET_W) > ex && by < (ey + ENE_HIGH) && (by + BULLET_HIGH) > ey) {
				++score; // 碰撞成功，分数加1
				// 碰撞：先删除子弹，再删除敌机（顺序对向后遍历无影响）
				bulletX.erase(bulletX.begin() + b);
				bulletY.erase(bulletY.begin() + b);

				eneX.erase(eneX.begin() + c);
				eneY.erase(eneY.begin() + c);

				// 敌机已被删除，跳出内层循环，进入下一个敌机
				break;
			}
		}
	}
}

#endif