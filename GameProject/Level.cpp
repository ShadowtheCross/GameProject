#include "LevelBuilding.h"
#include "GameState.h"
#include "GameLogic.h"


Level::Level(GameState* gs, std::string name) : GameObject(gs, name), Drawer(gs, name + "Builder") {
	MC = new MainCharacter(gs, "MainCharacter");
	g = new Goblin(gs);
	s = new Skeleton(gs);
}

void Level::init(std::string constructionFile, std::string texturesFile) {
	Drawer::init(constructionFile, texturesFile);
	MC->init(1, 1, 1, 12,
		"Assets\\Textures\\MC\\", "Assets\\Textures\\MC\\Animations.txt",
		2.0/3.0 ,2.0/ 3.0, 0, 0);
	g->init(16, 0);
	s->init(2, 0);
}

void Level::update(float dt) {
	Drawer::update();
	MC->update(dt);
	g->update(dt);
	s->update(dt);
}

void Level::draw() {
	Drawer::draw();
	MC->draw();
	g->draw();
	s->draw();
}

Level::~Level() {
	delete MC,g;
	
}