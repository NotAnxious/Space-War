// Bullet.h

#ifndef BULLET_H
#define BULLET_H

#include "Utils.h"
#include "Enemy.h"
#include <vector>

struct Bullet {
	double x;
	double y;
};

class BulletManager {
public:
	BulletManager() : bulletSpeed(5.0), lastFireTime(0.0) {}

	void update();
	void fire(double shipX);
	void removeBullet(int index);
	void render();

	int checkCollisions(EnemyManager* enemyManager);

	int getCount() const { return static_cast<int>(bullets.size()); }
	Bullet getBullet(int index) const { return bullets[index]; }

	static const int BULLET_WIDTH = 64;
	static const int BULLET_HEIGHT = 322;

private:
	std::vector<Bullet> bullets;
	double bulletSpeed;
	double lastFireTime;
};

inline void BulletManager::update() {
	for (auto& bullet : bullets) {
		bullet.y -= bulletSpeed;
	}

	for (int i = static_cast<int>(bullets.size()) - 1; i >= 0; --i) {
		if (bullets[i].y <= -BULLET_HEIGHT) {
			bullets.erase(bullets.begin() + i);
		}
	}
}

inline void BulletManager::fire(double shipX) {
	double currentTime = glfwGetTime();
	if (KEY_DOWN(VK_LBUTTON) && currentTime - lastFireTime >= 0.1) {
		bullets.push_back({ shipX + 100.0, -322.0 });
		lastFireTime = currentTime;
	}
}

inline void BulletManager::removeBullet(int index) {
	if (index >= 0 && index < static_cast<int>(bullets.size())) {
		bullets.erase(bullets.begin() + index);
	}
}

inline void BulletManager::render() {
	glColor3f(1.0f, 0.0f, 0.0f); // 红色子弹
	glBegin(GL_QUADS);

	for (const auto& bullet : bullets) {
		float x = static_cast<float>(bullet.x);
		float y = static_cast<float>(bullet.y);
		float width = BULLET_WIDTH * 1.0f;
		float height = BULLET_HEIGHT * 1.0f;

		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);
	}
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f); // 恢复白色
}

inline int BulletManager::checkCollisions(EnemyManager* enemyManager) {
	int score = 0;

	for (int b = static_cast<int>(bullets.size()) - 1; b >= 0; --b) {
		for (int e = static_cast<int>(enemyManager->getCount()) - 1; e >= 0; --e) {
			const Enemy& enemy = enemyManager->getEnemy(e);
			const Bullet& bullet = bullets[b];

			double bx = bullet.x;
			double by = bullet.y;
			double ex = enemy.x;
			double ey = enemy.y;

			if (bx < (ex + EnemyManager::ENEMY_WIDTH) &&
				(bx + BULLET_WIDTH) > ex &&
				by < (ey + EnemyManager::ENEMY_HEIGHT) &&
				(by + BULLET_HEIGHT) > ey) {

				++score;
				removeBullet(b);
				enemyManager->removeEnemy(e);
				break;
			}
		}
	}

	return score;
}

#endif
