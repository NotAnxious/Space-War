#ifndef ENE_H
#define ENE_H

#include <vector>
#include <main.h>
using namespace std;
vector<int> eneX = { 100,200 };
vector<int> eneY = { 200,100 };
IMAGE enePng;

void RefreshENEPosit() {
	for (int i = 0; i < eneY.size(); ++i) {
		eneY[i] += 1.0;
	}
}
void eneOutOfScreenDetection(int sereenSize) {
	for (int i = 0; i < eneY.size(); ++i) {
		if (eneY[i] >= sereenSize) {
			// 删除越界的敌机
			auto iter = eneY.erase(eneY.begin() + 1);
			auto iter = eneX.erase(eneX.begin() + 1);
		}
	}
}
/*bool collisionDetection() {
	for (int i = 0; i < eneY.size(); ++i) {
		if (eneY[i] < ) {
		}
	}
}*/

#endif