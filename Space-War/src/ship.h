// Ship.h

#ifndef SHIP_H
#define SHIP_H

#include "Texture.h"
#include "Utils.h"

const double SHIP_SPEED_FACTOR = 50.0;

class Ship {
public:
	Ship(double startX, double scrWidth)
		: x(startX), velocity(0.0), screenWidth(scrWidth), directionLeft(false) {}
	void update(double deltaTime);
	void render();
	double getX() const { return x; }
	Texture texture;

	const int shipImageWidth = 174;
	const int shipImageHeight = 228;

private:
	double x;
	double velocity;
	double screenWidth;
	bool directionLeft;
};

inline void Ship::update(double deltaTime) {
	double timeScale = deltaTime * SHIP_SPEED_FACTOR;

	if (KEY_DOWN('A')) { directionLeft = true; }
	if (KEY_DOWN('D')) { directionLeft = false; }

	if (directionLeft) {
		velocity -= 100.0 * timeScale;
	}
	else {
		velocity += 100.0 * timeScale;
	}

	x += velocity * timeScale;

	if (x > screenWidth) { x = -shipImageWidth; }
	if (x < -shipImageWidth) { x = screenWidth; }
}

inline void Ship::render() {
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(static_cast<float>(x), 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(static_cast<float>(x) + texture.width * 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(static_cast<float>(x) + texture.width * 1.0f, texture.height * 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(static_cast<float>(x), texture.height * 1.0f);
	glEnd();
}

#endif
