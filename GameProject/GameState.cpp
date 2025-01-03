#include "GameLogic.h"

#ifndef GAMESTATE.H
#include "GameState.h"
#endif
#include <cmath>
#include "LevelBuilding.h"

GameState::GameState()  {
	x_global = &x;
	y_global = &y;
	player_x = &x;
	player_y = &y;
	OffsetX = Config::window_width / 2;
	OffsetY = Config::window_height / 2;
	Handler = new EntityHandler(this);
	Menu = new MainPlayerMenu(this);
}

void GameState::update(float dt) {
	if (onTheMenu) {
		Menu->update(dt);
		return;
	}
	if (goToTheNextLevel) {
		Handler->wipeEntities();
		Handler->clearStaticEntities();
		Handler->teleportPlayer(0, 0);
		DungeonDrawer* temp = ActiveLevel;
		ActiveLevel = load("Level" + std::to_string(currentLevel), this);
		delete temp;
		goToTheNextLevel = false;
	}





	ActiveLevel->update(dt); 
	Handler->update(dt);
}
void GameState::init(int BlockS,std::string ConstructionFile, std::string texturesFile) {
	Menu->init();
	BlockSize = BlockS;
	Handler->init();
}
void GameState::draw() {
	if (onTheMenu) {
		Menu->draw();
		return;
	}
	if(ActiveLevel!= nullptr)
	ActiveLevel->draw();
	Handler->draw();
}
void GameState::backToMenu() {
	Handler->wipeEntities();
	Handler->clearStaticEntities();
	delete ActiveLevel;
	currentLevel = 0;
}


void GameState::teleportPlayer(float x, float y) {
	Handler->teleportPlayer(x, y);
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
	delete ActiveLevel, Handler;
}

float GameState::getGlobalX() {
	return (*x_global)+OffsetX - (*player_x)*BlockSize;
}
float GameState::getGlobalY() {
	return (*y_global) +OffsetY -(*player_y)*BlockSize;
}

float GameState::getPlayerX() {
	return (*player_x);
}
float GameState::getPlayerY() {
	return (*player_y);
}

void GameState::setPlayerX(float* X) {
	player_x = X;
}
void GameState::setPlayerY(float* Y) {
	player_y = Y;
}

void GameState::wipeEnemies() {
	Handler->wipeEntities();
}

void GameState::appendEntity(Entity* en) {
	Handler->appendEntity(en);
}

void GameState::appendStaticEntity(StaticEntity* en) {
	Handler->appendStaticEntity(en);
}

void GameState::wipeStaticEnemies() {
	Handler->clearStaticEntities();
}

void GameState::setGlobalX(float* X) {
	x_global = X;
}
void GameState::setGlobalY(float* Y) {
	y_global = Y;
}

void GameState::damagePlayer(float dmg) {
	Handler->damagePlayer(dmg);
}

void GameState::damageEnemies(float dmg) {
	Handler->damageEnemies(dmg);
}

void GameState::nextLevel() {
	onTheMenu = false;
	goToTheNextLevel = true;
	currentLevel++;
	
}



int GameState::getBlockSize() {
	return BlockSize;
}
