#ifndef ENE_H
#define ENE_H

#include <vector>
#include "main.h"
using namespace std;
vector<int> eneX;
vector<double> eneY;

// ene长和高
const int enePngX = 242;

// ene速度相关变量
const double eneSpeedFactor = 200.0;
double eneTimeScale;

void RefreshENEPosit(double deltaTime) {
	eneTimeScale = deltaTime * eneSpeedFactor;
	
	for (int i = 0; i < eneY.size(); ++i) {
		eneY[i] -= eneTimeScale;
	}
}

void eneOutOfScreenDetection(int screenHeight) {
	for (int i = static_cast<int>(eneY.size()) - 1; i >= 0; --i) {
		if (eneY[i] < (0-enePngX)) {
			spdlog::debug("DELETING enemy at Y: {}", eneY[i]);
			eneY.erase(eneY.begin() + i);
			eneX.erase(eneX.begin() + i);
		}
	}
}

void addENE(int xPos, int screenHeight) {
	spdlog::debug("ADDED enemy at Y: {}", screenHeight);
	eneX.push_back(xPos);
	eneY.push_back(static_cast<double>(screenHeight));
}


#endif
