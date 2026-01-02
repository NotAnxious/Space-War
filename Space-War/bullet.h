#ifndef BULLET_H
#define BULLET_H

#include <main.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
IMAGE bulletPng;
vector<int> bulletX;
vector<int> bulletY;
void createbullet(int x,int y) {
	if (KEY_DOWN(VK_LBUTTON)) {
		bulletX.push_back(x);
		bulletY.push_back(y - 322);
	}
}

#endif