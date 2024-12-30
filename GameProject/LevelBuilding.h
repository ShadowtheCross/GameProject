#pragma once

#include "sgg/graphics.h"
#include "GameLogic.h"
#include <iostream>
#include <unordered_map>
#include "BorderMapManagement.h"
#include <vector>
#include "RandomGet.h"
#include "Miscallenious.h"
#include "Character.h"



class Block : protected GameObject{
private:
	float x, y;
	graphics::Brush* b;
	

public:
	static Block* declareAndInit(GameState* gs, std::string name,  int x_cord, int y_cord, graphics::Brush* toUse);



	Block(GameState* gs, std::string name);

	void init(float x_cord, float y_cord, graphics::Brush* toUse);
	void draw();
	void update();
	void drawDebug();
	~Block();
};

/*
	* World Building Methods
	*
	* Will be used by init to construct the play world
	*
*/


class Drawer : protected GameObject {
protected:
	std::unordered_map<int, std::unordered_map<int, Block*> > Blocks;
	std::unordered_map<int, BlockBorder*>  Border;


	class RandomBrush BackGround,
		Ceiling, DownStairs, DownStairsCeiling,
		Ground, GroundRight, LeftWall, OutsideMap, RightWall,
		UpStairs, UpStairsCeiling;
	int x_next, y_next;

	void drawStart();
	void drawEnd();

	void drawLine(int n);

	void drawUpStairs(int n);

	void drawDownStairs(int n);

	void drawDropDown(int n);
	
	void drawCavern(int n);


public:

	Drawer(GameState* gs, std::string name);

	void init(std::string constructionFile,std::string texturesFile);
	void update();
	void draw();
	
	~Drawer();

};

class Level : public Drawer, public GameObject {


public:

	
	class MainCharacter* MC;
	class Goblin* g;
	class Skeleton* s;
	Level(GameState* gs, std::string name);
	

	void init(std::string constructionFile, std::string texturesFile);
	void update(float dt);
	void draw();



	~Level();



};