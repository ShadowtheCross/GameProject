#pragma once
#include "sgg/graphics.h"
#include "GameLogic.h"
#include <iostream>
#include <unordered_map>
#include "BorderMapManagement.h"
#include <vector>
#include "RandomGet.h"
#include "Miscallenious.h"
#include "Entities.h"
#include "Config.h"


/*
* General Block Class
* 
*/

class Block : protected GameObject{
private:
	float x, y;
	graphics::Brush* b;
	

public:
	static Block* declareAndInit(GameState* gs, std::string name,  int x_cord, int y_cord, graphics::Brush* toUse);



	Block(GameState* gs, std::string name);

	void init(float x_cord, float y_cord, graphics::Brush* toUse);
	void draw();
	void update(float dt);
	void drawDebug();
	~Block();
};

/*
* 
* Class enemy spawn Block
* 
*/

class EnemyBlock : public Block {

public:
	static EnemyBlock* declareAndInit(GameState* gs, std::string name, int x_cord, int y_cord,graphics::Brush* toUse,int rate);


	EnemyBlock(GameState* gs, std::string name);
	void init(float x_cord, float y_cord, graphics::Brush* toUse,int spawnRate);
	void draw();
	void update(float dt);
	~EnemyBlock();


};






/*
	* World Building Methods
	*
	* Will be used by init to construct the play world
	*
*/


class DungeonDrawer : protected GameObject {
private:
	void loadTexturesPerNum(std::string file);
protected:
	std::unordered_map<int, std::unordered_map<int, Block*> > Blocks;
	std::unordered_map<int, BlockBorder*>  Border;
	std::unordered_map<std::string, int> TexturesNum;



	class RandomBrush BackGround,
		Ceiling, HalfCeilingUp, HalfBlockUp, HalfCeilingDown, HalfBlockDown, LeftEdge, RightEdge,
		Ground, GroundRight, LeftWall, OutsideMap, RightWall;
	int x_next, y_next;

	void drawStart();
	void drawEnd();

	void drawLine(int n);

	void drawUpBlocks(int n);

	void drawDownBlocks(int n);

	

	void drawDropDown(int n);
	
	void drawCavern(int n);


public:

	DungeonDrawer(GameState* gs, std::string name);

	void init(std::string constructionFile,std::string texturesFile, std::string TexturesPerBlock);
	void update(float dt);
	void draw();
	
	~DungeonDrawer();

};




inline DungeonDrawer* load(std::string name, GameState* gs) {
	DungeonDrawer* newLevel;

	if (name == "Level1") {
		newLevel = new DungeonDrawer(gs, "Level1");
		std::cout << "LOad";
		newLevel->init( "Assets\\Level1.txt", "Assets\\Textures\\Level1\\", "Assets\\Textures\\Level1\\TextureNumbers.txt");
		return newLevel;
	}
	if (name == "Level2") {
		newLevel = new DungeonDrawer(gs, "Level1");
		newLevel->init("Assets\\Level2.txt", "Assets\\Textures\\Level2\\","Assets\\Textures\\Level2\\TextureNumbers.txt");
		return newLevel;
	}
	return nullptr;


}