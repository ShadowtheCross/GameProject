#include "sgg/graphics.h"
#include "GameState.h"
#include "Config.h"
#include <iostream>

GameState *game;
float count =0.0f;
void draw() {
	game->instance->draw();
}
void update(float dt) {
	game->instance->update(dt);
	count += graphics::getDeltaTime();
	
}

int main(void) {

	graphics::createWindow(Config::window_width, Config::window_height,"Game");
	graphics::setCanvasSize(1000, 1000);
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
	
	game->createInstance();

	game->instance->init(256,"Assets\\Level1.txt", "Assets\\Textures\\Level\\");

	graphics::startMessageLoop();




}