#include "GameLogic.h"

#ifndef GAMESTATE.H
#include "GameState.h"
#endif
#include <cmath>
#include "LevelBuilding.h"


GameState::GameState() {



	x_global = &x;
	y_global = &y;
	player_x = &x;
	player_y = &y;
	OffsetX = Config::window_width / 2;
	OffsetY = Config::window_height / 2;
	Menu = new MainPlayerMenu(this);
	transition = new BlackScreen(this);
}

void GameState::update(float dt) {
	//Player Wins
	if (victory && victoryTimer.isRunning()) {
		Handler->damageEnemies(100000);
		float elapse = victoryTimer;
		if (!victoryTimer.isRunning()) {
			victory = false;
			backToMenu();
		}
	}
	//Player Dies
	if (defeat && defeatTimer.isRunning()) {
		Handler->wipeEntities();
		float elapse = defeatTimer;
		if (!defeatTimer.isRunning()) {
			defeat = false;
			backToMenu();
		}
	}



	//From the title Screen
	if (onTheMenu) {
		Menu->update(dt);
		if (!onTheMenu) {
			Handler = new EntityHandler(this);
			Handler->init();
			ActiveLevel =loadLevel("Level" + std::to_string(currentLevel), this);
			goToTheNextLevel = false;
			transition->deactivate();
		}
		return;
	}
	//Level To Level Transition
	if (goToTheNextLevel) {
		transition->activate();
	}
	if (goToTheNextLevel && transition->isActivated()) {
		Handler->wipeEntities();
		Handler->clearStaticEntities();
		Handler->teleportPlayer(0, 0);
		Drawer* temp = ActiveLevel;
		ActiveLevel = loadLevel("Level" + std::to_string(currentLevel), this);
		
		goToTheNextLevel = false;
		transition->deactivate();
	}

	//Update Parameters
	transition->update(dt);
	ActiveLevel->update(dt);
	Handler->update(dt);
}
void GameState::init(int BlockSize) {
	Menu->init();
	this->BlockSize = BlockSize;
	transition->init();
}
void GameState::draw() {

	if (onTheMenu) {
		Menu->draw();
		return;
	}
	if (victory) {
		graphics::setFont("Assets\\Fonts\\Oi-Regular.ttf");
		int c_x = Config::window_width / 4;
		int c_y = Config::window_height/ 2;
		graphics::drawText(c_x, c_y-100 , 50, "Victory  Achieved", Plain);
		graphics::drawText(c_x, c_y+100 , 50, "Thanks  For  Playing", Plain);
	} if (defeat) {
		graphics::setFont("Assets\\Fonts\\Oi-Regular.ttf");
		int c_x = Config::window_width / 4;
		int c_y = Config::window_height / 2;
		graphics::drawText(c_x, c_y - 100, 50, "!!!DEATH!!!", Plain);
		graphics::drawText(c_x, c_y + 100, 50, "You have Failed", Plain);
	}

	if(ActiveLevel!= nullptr)
	ActiveLevel->draw();
	Handler->draw();
	transition->draw();

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
	delete ActiveLevel, Handler,transition;
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

void GameState::appendEntity(Character* en) {
	Handler->appendEntity(en);
}

void GameState::appendStaticEntity(StaticEntity* en) {
	Handler->appendStaticEntity(en);
}

void GameState::wipeStaticEnemies() {
	Handler->clearStaticEntities();
}

void GameState::setAgro(bool val) {
	AgroByDefault = val;
}
bool GameState::getAgro() {
	return AgroByDefault;
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

void GameState::playerDamageEnemies(float dmg) {
	Handler->playerDamageEnemies(dmg);
}

void GameState::nextLevel() {
	onTheMenu = false;
	goToTheNextLevel = true;
	currentLevel++;
	if (currentLevel == 5) {
		setAgro(true);
	}
	else {
		setAgro(false);
	}
}

int GameState::getBlockSize() {
	return BlockSize;
}

void GameState::regenerateHealth(float Health) {
	Handler->regeneratePlayerHealth(Health);
}
void GameState::increaseHealth(float Health) {
	Handler->increasePlayerHealth(Health);
}

void GameState::playerWon() {
	victory = true;
	victoryTimer.start();	
}
void GameState::playerLost() {
	defeat = true;
	defeatTimer.start();
}

void GameState::backToMenu() {
	AgroByDefault = false;
	currentLevel = 0;
	onTheMenu = true;
	goToTheNextLevel = false;
	if (ActiveLevel != nullptr) {
		delete ActiveLevel;
		ActiveLevel = nullptr;
	}
	if (Handler != nullptr) {
		delete Handler;
		Handler = nullptr;
	}
	graphics::setFont("Assets\\Fonts\\ImperialScript-Regular.ttf");
	graphics::playMusic("Assets\\SoundTrack\\MainMenu\\Price_Of_Freedom - Good_B_Music.mp3", 0.2);

	
}


bool GameState::enemiesInRange(float x, float range) {
	return Handler->enemiesInRange(x, range);
}