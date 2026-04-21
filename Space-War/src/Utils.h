// Utils.h

#ifndef UTILS_H
#define UTILS_H

#include <Windows.h>
#include <cstdlib>

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)

inline long getRand(long randmin, long randmax) {
	return (rand() % (randmax - randmin + 1)) + randmin;
}

#endif
