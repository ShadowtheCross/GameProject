#include "sgg/graphics.h"
#include "GameState.h"
#include "Config.h"
#include <iostream>
#include "MainMenu.h"

GameState *game;

void draw() {
	game->instance->draw();
}

void update(float dt) {
	game->instance->update(dt);
}

int main(void) {

	graphics::createWindow(Config::window_width, Config::window_height,"Monster Slayer");
	graphics::setCanvasSize(1000, 1000);
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);	
	game->createInstance();
	game->instance->init(256);
	graphics::startMessageLoop();




}