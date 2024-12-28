#include "LevelBuilding.h"
#include "GameState.h"
#include "GameLogic.h"

Level::Level(GameState* gs, std::string name) : GameObject(gs, name), Drawer(gs, name + "Builder") {
	MC = new MainCharacter(gs, "MainCharacter");
}

void Level::init(std::string constructionFile, std::string texturesFile) {
	Drawer::init(constructionFile, texturesFile);
	MC->init(20, 1, 4560, 5,
		"Assets\\Textures\\MC\\", "Assets\\Textures\\MC\\Animations.txt",
		2.0/3.0 ,2.0/ 3.0, 0, 0);
}

void Level::update(float dt) {
	Drawer::update();
	MC->update(dt);
}

void Level::draw() {
	Drawer::draw();
	MC->draw();
}

Level::~Level() {
	delete MC;
}