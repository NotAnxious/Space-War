// main.cpp

#define GLFW_INCLUDE_NONE
#include "glad.h"
#include <GLFW/glfw3.h>
#include "Game.h"
#include <spdlog/spdlog.h>
#include <conio.h>

int main() {
	spdlog::info("Program starting...");

	Game game(1920, 1080);

	if (!game.init()) {
		spdlog::error("Game initialization failed!");
		spdlog::info("Press any key to exit...");
		return -1;
	}

	game.run();

	spdlog::info("Final score: {}", game.getScore());
	spdlog::info("Press any key to exit...");

	return 0;
}
