// Enemy.h

#ifndef ENEMY_H
#define ENEMY_H

#include "Utils.h"
#include "Texture.h"
#include <vector>
#include <spdlog/spdlog.h>

struct Enemy {
	double x;
	double y;
};

class EnemyManager {
public:
	EnemyManager(double scrWidth, double scrHeight)
		: screenWidth(scrWidth), screenHeight(scrHeight), speedFactor(200.0) {}

	void update(double deltaTime);
	void render();
	void spawnEnemy(int xPos);
	void removeEnemy(int index);

	int getCount() const { return static_cast<int>(enemies.size()); }
	Enemy getEnemy(int index) const { return enemies[index]; }

	Texture texture;

	static const int ENEMY_WIDTH = 400;
	static const int ENEMY_HEIGHT = 242;

private:
	std::vector<Enemy> enemies;
	double screenWidth;
	double screenHeight;
	double speedFactor;
};

inline void EnemyManager::update(double deltaTime) {
	double timeScale = deltaTime * speedFactor;

	for (auto& enemy : enemies) {
		enemy.y -= timeScale;
	}

	for (int i = static_cast<int>(enemies.size()) - 1; i >= 0; --i) {
		if (enemies[i].y < -ENEMY_HEIGHT) {
			spdlog::debug("DELETING enemy at Y: {}", enemies[i].y);
			enemies.erase(enemies.begin() + i);
		}
	}
}

inline void EnemyManager::render() {
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBegin(GL_QUADS);

	for (const auto& enemy : enemies) {
		float x = static_cast<float>(enemy.x);
		float y = static_cast<float>(enemy.y);
		float width = texture.width * 1.0f;
		float height = texture.height * 1.0f;

		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(x, y);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(x + width, y);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(x + width, y + height);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(x, y + height);
	}
	glEnd();
}

inline void EnemyManager::spawnEnemy(int xPos) {
	spdlog::debug("ADDED enemy at Y: {}", screenHeight);
	enemies.push_back({ static_cast<double>(xPos), screenHeight });
}

inline void EnemyManager::removeEnemy(int index) {
	if (index >= 0 && index < static_cast<int>(enemies.size())) {
		enemies.erase(enemies.begin() + index);
	}
}

#endif
