#include "LevelBuilding.h"


FinalBossDrawer::FinalBossDrawer(GameState* gs, std::string name) : Drawer(gs, name) {

}

void FinalBossDrawer::init(std::string constructionFile, std::string texturesFile, std::string TexturesPerBlock) {
	Drawer::init(constructionFile, texturesFile, TexturesPerBlock);
	Ground.setup("Assets\\Textures\\Level5\\Ground", TexturesNum["Ground"]);
	BottomRightEdge.setup("Assets\\Textures\\Level5\\BottomRightEdge", TexturesNum["BottomRightEdge"]); 
	UpperLeftEdge.setup("Assets\\Textures\\Level5\\UpperLeftEdge", TexturesNum["UpperLeftEdge"]);
	UpperRightEdge.setup("Assets\\Textures\\Level5\\UpperRightEdge", TexturesNum["UpperRightEdge"]);
	BottomLeftEdge.setup("Assets\\Textures\\Level5\\BottomLeftEdge", TexturesNum["BottomLeftEdge"]);
	BottomRightEdge.setup("Assets\\Textures\\Level5\\BottomRightEdge", TexturesNum["BottomRightEdge"]);
	OutsideMap.setup("Assets\\Textures\\Level5\\OutsideMap", TexturesNum["OutsideMap"]);
	RightWall.setup("Assets\\Textures\\Level5\\RightWall", TexturesNum["RightWall"]);
	LeftWall.setup("Assets\\Textures\\Level5\\LeftWall", TexturesNum["LeftWall"]); 
	BackGround.setup("Assets\\Textures\\Level5\\BackGround", TexturesNum["BackGround"]);
	Ceiling.setup("Assets\\Textures\\Level5\\Ceiling", TexturesNum["Ceiling"]);
	//draw drop
	for (int i = -100; i < 10; i++) {
		addBlock(0, i, BackGround.random());
		addBlock(-1, i, RightWall.random());
		addBlock(1, i, LeftWall.random());
	}	
	Border[0] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0, 103.5f,
		0, -90000.5);
	Border[-1] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0, 103.5f,
		0, +101.5);
	Border[+1] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0, 103.5f,
		0, +101.5);


	//RightWall
	addBlock(-6, -101, BottomRightEdge.random());
	addBlock(-6, -102, RightWall.random());
	addBlock(-6, -103, RightWall.random());
	addBlock(-6, -104, UpperRightEdge.random());
	


	//draw the arena
	for (int x = -5; x < -1; x++) {
		addBlock(x, -101, Ceiling.random());
		addBlock(x, -102, BackGround.random());
		addBlock(x, -103, BackGround.random());
		addBlock(x, -104, Ground.random());
		Border[x] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0, 103.5f,
			0, +101.5);
	}
	//Falling Blocks
	for (int x = -1; x < 2; x++) {
		if(x != 0)	addBlock(x, -101, Ceiling.random());
		else addBlock(x, -101, BackGround.random());
		addBlock(x, -102, BackGround.random());
		addBlock(x, -103, BackGround.random());
		addBlock(x, -104, Ground.random());

	}



	for (int x = 2; x < 15; x++) {
		addBlock(x, -101, Ceiling.random());
		addBlock(x, -102, BackGround.random());
		addBlock(x, -103, BackGround.random());
		addBlock(x, -104, Ground.random());
		Border[x] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0, 103.5f,
			0, +101.5);

	}

	/*
	* Create the entry points where enemies spawn in
	*/
	addBlock(-3, -101, BackGround.random());
	for (int y = 1; y < 4; y++) {
		addBlock(-2, -101+y, BackGround.random());
		addBlock(-3, -101 + y, LeftWall.random());
		addBlock(-4, -101 + y, RightWall.random());
	}
	Border[-3] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0, +103.5,
		0, +0);
	/*
	* 
	* Second spawn point drop
	* 
	*/
	addBlock(+8, -101, BackGround.random());

	for (int y = 1; y < 4; y++) {
		addBlock(8, -101 + y, BackGround.random());
		addBlock(9, -101 + y, LeftWall.random());
		addBlock(7, -101 + y, RightWall.random());
	}
	Border[8] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0, +103.5,
		0, +0);


	addBlock(15, -101, BottomLeftEdge.random());
	addBlock(15, -102, LeftWall.random());
	addBlock(15, -103, LeftWall.random());
	addBlock(15, -104, UpperLeftEdge.random());

	for (int x = -20; x < 30; x++) {
		fillLowerY(x, -99, 100);
		fillUpperY(x, -100, 120);
	}

	Boss* finalBoss = new Boss(GameObject::m_state);
	finalBoss->init(10, 102);
	GameObject::m_state->appendEntity(finalBoss);
	GameObject::m_state->setAgro(true);

}

void FinalBossDrawer::update(float dt) {
	Drawer::update(dt);
}

void FinalBossDrawer::draw() {
	Drawer::draw();
}

FinalBossDrawer::~FinalBossDrawer() {

}
