#pragma once
#include "GameLogic.h"
#include <iostream>
#include "LevelBuilding.h"
#include <unordered_map>
#include "BorderMapManagement.h"
#include "Entities.h"
#include "EntityManagement.h"
#include "Movement.h"
#include "MainMenu.h"
#include "BlackScreen.h"

class GameState {
public:
	class BlackScreen* transition;
private:
	float* x_global, * y_global;
	float x =0, y=0,BlockSize =256;
	float* player_x, * player_y;
	int OffsetX, OffsetY;
	bool onTheMenu = true,goToTheNextLevel= false;
	int currentLevel = 0;
	

	GameState();
	class Drawer* ActiveLevel;
	class EntityHandler* Handler;
	std::unordered_map<int, class BlockBorder*> *blockRef ;

	class MainPlayerMenu *Menu;
	
public:

	void update(float dt);
	void init(int BlockSize,std::string constructionFile, std::string texturesFile);
	void draw();
	static void createInstance();
	static void deleteInstance();

	static GameState* instance;

	void setGlobalX(float*);
	void setGlobalY(float*);
	void setPlayerX(float*);
	void setPlayerY(float*);

	void regenerateHealth(float Health);
	void increaseHealth(float Health);



	void teleportPlayer(float x, float y);
	void setBorder(std::unordered_map<int, BlockBorder* > *ref);
	bool canGoAt(float x, float y);

	float getGlobalX();
	float getGlobalY();
	float getPlayerX();
	float getPlayerY();
	
	void appendStaticEntity(StaticEntity* en);
	void wipeStaticEnemies();

	void wipeEnemies();
	void appendEntity(Character* en);
	
	void damagePlayer(float dmg);
	void damageEnemies(float dmg);
public:
	void nextLevel();
	void backToMenu();

	int get_player_width();
	int get_player_height();
	int getBlockSize();

	~GameState();

};

