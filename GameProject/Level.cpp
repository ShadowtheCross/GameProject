#include "LevelBuilding.h"
#include "GameState.h"
#include "GameLogic.h"


Level::Level(GameState* gs, std::string name) : GameObject(gs, name), DungeonDrawer(gs, name + "Builder") {
}

void Level::init(std::string constructionFile, std::string texturesFile) {
	DungeonDrawer::init(constructionFile, texturesFile);
}

void Level::update(float dt) {
	DungeonDrawer::update();
}

void Level::draw() {
	DungeonDrawer::draw();
}

Level::~Level() {
	
}