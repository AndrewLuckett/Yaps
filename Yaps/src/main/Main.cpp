#include "../global/Shorts.h"
#include "../render/Window.h"
#include "../render/Renderer.h"
#include "../core/GameMain.h"
#include "../core/FrameCounter.h"
#include "../game/ParticleGame.h"
#include <queue>

int main() {
	window::init("Yet Another Particle Sim - Andrew Luckett 2021");
	window::myinit();

	glfwSwapInterval(0); //No vsync

	GameMain gameInst = GameMain(); //Top level system

	gameInst.addSubSystem(new FrameCounter()); //Comes first to draw on top
	gameInst.addSubSystem(new ParticleGame()); //The game

	std::queue<Model> renderArr; //Render queue

	/* Loop until the user closes the window */
	while (window::isRunning()) {
		gameInst.update(std::chrono::system_clock::duration());
		gameInst.getRenderArr(renderArr);

		renderer::clearScreen();

		while (!renderArr.empty()) {
			renderer::draw(renderArr.front());
			renderArr.pop();
		}

		renderer::pushToScreen();

	}

	gameInst.cleanup();
	window::close();

	return 0;
}