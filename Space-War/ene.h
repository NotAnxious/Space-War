#ifndef ENE_H
#define ENE_H

#include <vector>
#include <main.h>
using namespace std;
vector<int> eneX = {0,100};
vector<int> eneY = {0,100};
IMAGE enePng;

void RefreshENEPosit() {
	for (int i = 0; i < eneY.size(); ++i) {
		eneY[i] -= 1.0 / 30.0;
	}
}
void showENE() {
	for (int i = 0; i < eneX.size(); ++i) {
		showImage(NULL, eneX[i], eneY[i], &enePng);
	}
}

#endif