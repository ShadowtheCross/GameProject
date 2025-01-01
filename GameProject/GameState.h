#pragma once
#include "GameLogic.h"
#include <iostream>
#include "LevelBuilding.h"
#include <unordered_map>
#include "BorderMapManagement.h"
#include "Character.h"
#include "EntityManagement.h"

class GameState {
private:
	float* x_global, * y_global;
	float x =0, y=0,BlockSize =256;
	float* player_x, * player_y;
	int OffsetX, OffsetY;


	GameState();
	class Level *ActiveLevel;
	class EntityHandler* Handler;
	std::unordered_map<int, class BlockBorder*> *blockRef ;

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


	void setBorder(std::unordered_map<int, BlockBorder* > *ref);
	bool canGoAt(float x, float y);

	float getGlobalX();
	float getGlobalY();
	float getPlayerX();
	float getPlayerY();
	
	void wipeEnemies();
	void appendEntity(Entity* en);


	void changeLevel(Level* level) {
		ActiveLevel =  level;
	}

	int get_player_width();
	int get_player_height();
	int getBlockSize();

	~GameState();

};

