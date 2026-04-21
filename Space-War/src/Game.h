// Game.h

#ifndef GAME_H
#define GAME_H

#define GLFW_INCLUDE_NONE
#include "glad.h"
#include <GLFW/glfw3.h>
#include "Texture.h"
#include "Ship.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Utils.h"
#include <spdlog/spdlog.h>

class Game {
public:
	Game(int width, int height);
	~Game();

	bool init();
	void run();
	void shutdown();

	long long getScore() const { return score; }

private:
	void update(double deltaTime);
	void render();
	void checkCollisions();
	bool loadTextures();

	GLFWwindow* window;
	int screenWidth;
	int screenHeight;
	long long score;
	double lastEneSpawnTime;

	Texture starrySkyTexture;
	Texture spaceShipTexture;
	Texture eneTexture;
	Ship* ship;
	EnemyManager* enemyManager;
	BulletManager* bulletManager;
};

#endif
