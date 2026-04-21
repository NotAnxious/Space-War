// Game.cpp

#include "Game.h"

Game::Game(int width, int height)
	: window(nullptr), screenWidth(width), screenHeight(height),
	score(0), lastEneSpawnTime(0.0),
	ship(nullptr), enemyManager(nullptr), bulletManager(nullptr) {
}

Game::~Game() {
	shutdown();
}

bool Game::init() {
	spdlog::info("Initializing GLFW...");
	if (!glfwInit()) {
		spdlog::error("Failed to initialize GLFW!");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	spdlog::info("Creating window...");
	window = glfwCreateWindow(screenWidth, screenHeight, "Space War",
		glfwGetPrimaryMonitor(), nullptr);

	if (!window) {
		spdlog::error("Failed to create window!");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		spdlog::error("Failed to initialize GLAD!");
		glfwTerminate();
		return false;
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glfwSwapInterval(0);

	if (!loadTextures()) {
		return false;
	}

	ship = new Ship(screenWidth / 2.0, screenWidth);
	ship->texture = this->spaceShipTexture;

	enemyManager = new EnemyManager(screenWidth, screenHeight);
	enemyManager->texture = this->eneTexture;

	bulletManager = new BulletManager();

	return true;
}

bool Game::loadTextures() {
	spdlog::info("Loading textures...");

	if (!loadTexture("./png/starry-sky/starry-sky.png", starrySkyTexture)) {
		spdlog::error("Failed to load starry sky texture!");
		return false;
	}
	spdlog::info("Starry sky texture loaded.");

	if (!loadTexture("./png/spaceship/spaceship.png", spaceShipTexture)) {
		spdlog::error("Failed to load spaceship texture!");
		return false;
	}
	spdlog::info("Spaceship texture loaded.");

	if (!loadTexture("./png/spaceship_2/spaceship.png", eneTexture)) {
		spdlog::error("Failed to load enemy texture!");
		return false;
	}
	spdlog::info("Enemy spaceship texture loaded.");

	return true;
}

void Game::run() {
	spdlog::info("Entering main loop...");

	double lastTime = glfwGetTime();
	int frameCount = 0;
	double lastFpsUpdate = lastTime;

	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		frameCount++;
		if (currentTime - lastFpsUpdate >= 1.0) {
			double fps = frameCount / (currentTime - lastFpsUpdate);
			spdlog::debug("FPS: {:.2f}", fps);
			frameCount = 0;
			lastFpsUpdate = currentTime;
		}

		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		update(deltaTime);
		render();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void Game::update(double deltaTime) {
	double currentTime = glfwGetTime();

	ship->update(deltaTime);
	enemyManager->update(deltaTime);
	bulletManager->update();
	bulletManager->fire(ship->getX());

	if (currentTime - lastEneSpawnTime >= 1.0) {
		lastEneSpawnTime = currentTime;
		if (getRand(0, 1) == 0) {
			enemyManager->spawnEnemy(getRand(0, screenWidth));
		}
	}

	checkCollisions();
}

void Game::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, starrySkyTexture.id);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(static_cast<float>(screenWidth), 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(static_cast<float>(screenWidth), static_cast<float>(screenHeight));
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f, static_cast<float>(screenHeight));
	glEnd();

	enemyManager->render();
	ship->render();
	bulletManager->render();
}

void Game::checkCollisions() {
	score += bulletManager->checkCollisions(enemyManager);
}

void Game::shutdown() {
	delete ship;
	delete enemyManager;
	delete bulletManager;

	if (window) {
		glfwDestroyWindow(window);
		window = nullptr;
	}

	glfwTerminate();
}
