#ifndef ENE_H
#define ENE_H

#include <vector>
#include "main.h"
using namespace std;
vector<int> eneX;
vector<int> eneY;
IMAGE enePng;

void RefreshENEPosit() {
	for (int i = 0; i < eneY.size(); ++i) {
		eneY[i] += 1.0;
	}
}
void eneOutOfScreenDetection(int sereenSize) {
	for (int i = static_cast<int>(eneY.size()) - 1; i >= 0; --i) {
		if (eneY[i] >= sereenSize) {
			// 从末尾向前遍历并删除越界的敌机，避免索引失效与越界访问
			eneY.erase(eneY.begin() + i);
			eneX.erase(eneX.begin() + i);
		}
	}
}
void addENE(int xPos) {
	eneX.push_back(xPos);
	eneY.push_back(0);
}


#endif