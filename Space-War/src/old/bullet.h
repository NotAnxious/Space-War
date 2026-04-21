#ifndef BULLET_H
#define BULLET_H

#include "main.h"
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
vector<int> bulletX;
vector<int> bulletY;
// 碰撞检测的参数
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
			// 子弹超出屏幕范围，删除该子弹
			bulletY.erase(bulletY.begin() + i);
			bulletX.erase(bulletX.begin() + i);
		}
	}
}
void collisionDetection() {

	// 碰撞检测，检查子弹是否与敌人碰撞
	for (int c = static_cast<int>(eneY.size()) - 1; c >= 0; --c) {
		for (int b = static_cast<int>(bulletY.size()) - 1; b >= 0; --b) {
			int bx = bulletX[b];
			int by = bulletY[b];
			int ex = eneX[c];
			int ey = eneY[c];

			// AABB 碰撞检测
			if (bx < (ex + ENE_W) && (bx + BULLET_W) > ex && by < (ey + ENE_HIGH) && (by + BULLET_HIGH) > ey) {
				++score; // 成功得分+1
				// 删除子弹和敌人
				bulletX.erase(bulletX.begin() + b);
				bulletY.erase(bulletY.begin() + b);

				eneX.erase(eneX.begin() + c);
				eneY.erase(eneY.begin() + c);

				// 一次碰撞只能删除一个敌人，所以跳出内层循环
				break;
			}
		}
	}
}

#endif