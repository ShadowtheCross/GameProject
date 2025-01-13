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
#include "Back.h"

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

/*
* 
* This class will be the primary method all entities inherit
* 
*/

class Drawer : public GameObject {
private:
	std::unordered_map<int, std::unordered_map<int, Block*> > Blocks;
protected:

	std::unordered_map<int, BlockBorder*>  Border;
	std::unordered_map<std::string, int> TexturesNum;

	class RandomBrush OutsideMap;


	void loadTexturesPerNum(std::string file);

	int x_next, y_next;

	void addBlock(int x, int y, graphics::Brush* br);
	void addEnemyBlock(int x, int y, graphics::Brush* br);


	virtual void fillUpperY(int x_next, int y_next, int nBlocks);
	virtual void fillLowerY(int x_next, int y_next, int nBlocks);
	virtual void drawStart();
	virtual void drawEnd();
public:
	Drawer(GameState* gs, std::string name);

	virtual void init(std::string constructionFile, std::string texturesFile, std::string TexturesPerBlock);
	virtual void update(float dt);
	virtual void draw();
	virtual void drawExit(int x,int y);
	void drawChest(int x,int y);



	virtual ~Drawer();

};



class DungeonDrawer : public Drawer {
private:
	class RandomBrush BackGround,
		Ceiling, HalfCeilingUp, HalfBlockUp, HalfCeilingDown, HalfBlockDown, LeftEdge, RightEdge,
		Ground, GroundRight, LeftWall, RightWall, UpperRightEdge,
		UpperLeftEdge,	BottomRightEdge,BottomLeftEdge;
	

	void drawStart();
	void drawEnd();

	void drawLine(int n);

	void drawUpBlocks(int n);

	void drawDownBlocks(int n);

	

	void drawDropDown(int n);
	
	void drawCavern(int n);


public:

	DungeonDrawer(GameState* gs, std::string name);

	virtual void init(std::string constructionFile,std::string texturesFile, std::string TexturesPerBlock);
	virtual void update(float dt);
	virtual void draw();
	
	~DungeonDrawer();
};



class OpenMapDrawer : public Drawer {
	//For the cave exit
protected:
	class RandomBrush BackGround, RightWall, LeftWall, Ground, Ceiling,
		UpperRightEdge, UpperLeftEdge, BottomRightEdge, BottomLeftEdge,
		HalfBlock,DecorativeObjects;
	const float top = 100000;
	class VisualBackground* backPanel;
	void drawStart();
	void drawEnd();

	void drawLine(int n);

	void drawUpBlocks(int n);

	void drawDownBlocks(int n);

	void drawSpikeDrop(int n);

	void drawDropDown(int n);


//	void drawDropDown(int n);



public:

	OpenMapDrawer(GameState* gs, std::string name);

	virtual void init(std::string constructionFile, std::string texturesFile, std::string TexturesPerBlock);
	virtual void update(float dt);
	virtual void draw();
	virtual void drawExit(int x, int y);

	~OpenMapDrawer();

};

class FinalOpenMapDrawer : public OpenMapDrawer{
private:
	bool fallTrigger,levelTrigger;
	int trigger_y=0;
	
	virtual void drawExit(int x,int y);
public:
	FinalOpenMapDrawer(GameState* gs, std::string name);
	virtual void init(std::string constructionFile, std::string texturesFile, std::string TexturesPerBlock);
	virtual void update(float dt);
	virtual void draw();

	~FinalOpenMapDrawer();

};


class FinalBossDrawer : public  Drawer {
private:
	class RandomBrush Ground ,Ceiling,UpperLeftEdge ,
		UpperRightEdge ,BottomLeftEdge,	BottomRightEdge,OutsideMap,
		RightWall,LeftWall,BackGround;

public:


	FinalBossDrawer(GameState* gs, std::string name);
	virtual void init(std::string constructionFile, std::string texturesFile, std::string TexturesPerBlock);
	virtual void update(float dt);
	virtual void draw();

	~FinalBossDrawer();


};



inline Drawer* loadLevel(std::string name, GameState* gs) {
	Drawer* newLevel;
	
	graphics::stopMusic();
	if (name == "Level1") {
		graphics::playMusic("Assets\\SoundTrack\\Level1\\[Drumstep] - Tristam & Braken - Flight [Monstercat Release].mp3", 0.2);
		newLevel = new DungeonDrawer(gs, "Level1");
		newLevel->init( "Assets\\Level1.txt", "Assets\\Textures\\Level1\\", "Assets\\Textures\\Level1\\TextureNumbers.txt");
		return newLevel;
	}
	if (name == "Level2") {
		graphics::playMusic("Assets\\SoundTrack\\Level2\\Nitro Fun - New Game.mp3",0.2);
		newLevel = new DungeonDrawer(gs, "Level2");
		newLevel->init("Assets\\Level2.txt", "Assets\\Textures\\Level2\\","Assets\\Textures\\Level2\\TextureNumbers.txt");
		return newLevel;
	}
	if (name == "Level3") {
		graphics::playMusic("Assets\\SoundTrack\\Level3\\Swordsman of a Distant Star (Remix).mp3", 0.2);
		newLevel = new OpenMapDrawer(gs, "Level3");
		newLevel->init("Assets\\Level3.txt", "Assets\\Textures\\Level3\\", "Assets\\Textures\\Level3\\TextureNumbers.txt");
		return newLevel;
	}
	if (name == "Level4") {
		graphics::playMusic("Assets\\SoundTrack\\Level4\\Eerie Terraria.mp3", 0.2);
		newLevel = new FinalOpenMapDrawer(gs, "Level4");
		newLevel->init("Assets\\Level4.txt", "Assets\\Textures\\Level4\\", "Assets\\Textures\\Level4\\TextureNumbers.txt");
		return newLevel;
	}
	
	graphics::playMusic("Assets\\SoundTrack\\Level5\\meganeko - The Cyber Grind (Ultrakill Soundtrack).mp3", 0.2);
	newLevel = new FinalBossDrawer(gs, "Level5");
	newLevel->init("Assets\\Level5.txt", "Assets\\Textures\\Level5\\", "Assets\\Textures\\Level5\\TextureNumbers.txt");
	return newLevel;



}