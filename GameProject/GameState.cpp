#include "GameLogic.h"

#ifndef GAMESTATE.H
#include "GameState.h"
#endif
#include <cmath>
#include "LevelBuilding.h"


GameState::GameState()  {
	x_global = &x;
	y_global = &y;
	player_width = Config::mainPlayerWidth;
	player_height = Config::mainPlayerHeight;

}

void GameState::update(float dt) {
	current->update(dt); 
	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		x-=3;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		x+=3;
	}
	if (graphics::getKeyState(graphics::SCANCODE_S)) {
		y-=3;
	}
	if (graphics::getKeyState(graphics::SCANCODE_W)) {
		y+=3;
	}

}
void GameState::init(int BlockS,std::string ConstructionFile, std::string texturesFile) {
	BlockSize = BlockS;
	current = new Level(instance, "Level1");
	current->init(ConstructionFile, texturesFile);
	
	
}
void GameState::draw() {
	current->draw();



}

void GameState::createInstance() {
	if (GameState::instance == nullptr) {
		GameState::instance = new GameState();
	}
	
}

void GameState::deleteInstance() {
	if (GameState::instance != nullptr) {
		delete GameState::instance;
	}
}
void GameState::setBorder(std::unordered_map<int, BlockBorder*>* ref) {
	blockRef = ref;
}

bool GameState::canGoAt(float x, float y) {
	int k = std::round(x);
	if (blockRef == nullptr) {		
		return false;
	}
	else if(  (*blockRef)[k] != 0 )   {

		return blockRef->at(k)->canGoAt(x, y);
	}
	return false;

}


GameState::~GameState() {
	delete current;
}

float GameState::getGlobalX() {
	return (*x_global);
}
float GameState::getGlobalY() {
	return (*y_global);
}

void GameState::setGlobalX(float* X) {
	x_global = X;
}
void GameState::setGlobalY(float* Y) {
	y_global = Y;
}

int GameState::get_player_width() {
	return player_width;
}
int GameState::get_player_height() {
	return player_height;
}

int GameState::getBlockSize() {
	return BlockSize;
}
