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
		Blocks[0][i] = (Block::declareAndInit(GameObject::m_state, "", 0, i, BackGround.random()));
		Blocks[-1][i] = (Block::declareAndInit(GameObject::m_state, "", -1, i, RightWall.random()));
		Blocks[+1][i] = (Block::declareAndInit(GameObject::m_state, "", +1, i, LeftWall.random()));
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

	Blocks[-6][-101] = (Block::declareAndInit(GameObject::m_state, "", -6, -101, BottomRightEdge.random()));
	Blocks[-6][-102] = (Block::declareAndInit(GameObject::m_state, "", -6, -102, RightWall.random()));
	Blocks[-6][-103] = (Block::declareAndInit(GameObject::m_state, "", -6, -103, RightWall.random()));
	Blocks[-6][-104] = (Block::declareAndInit(GameObject::m_state, "", -6, -104, UpperRightEdge.random()));
	


	//draw the arena
	for (int x = -5; x < -1; x++) {
		Blocks[x][-101] = (Block::declareAndInit(GameObject::m_state, "", x, -101, Ceiling.random()));
		Blocks[x][-102] = (Block::declareAndInit(GameObject::m_state, "", x, -102, BackGround.random()));
		Blocks[x][-103] = (Block::declareAndInit(GameObject::m_state, "", x, -103, BackGround.random()));
		Blocks[x][-104] = (Block::declareAndInit(GameObject::m_state, "", x, -104, Ground.random()));
		Border[x] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0, 103.5f,
			0, +101.5);
	}
	//Falling Blocks
	for (int x = -1; x < 2; x++) {
		if(x != 0)	Blocks[x][-101] = (Block::declareAndInit(GameObject::m_state, "", x, -101, Ceiling.random()));
		else Blocks[x][-101] = (Block::declareAndInit(GameObject::m_state, "", x, -101, BackGround.random()));
		Blocks[x][-102] = (Block::declareAndInit(GameObject::m_state, "", x, -102, BackGround.random()));
		Blocks[x][-103] = (Block::declareAndInit(GameObject::m_state, "", x, -103, BackGround.random()));
		Blocks[x][-104] = (Block::declareAndInit(GameObject::m_state, "", x, -104, Ground.random()));
	}



	for (int x = 2; x < 15; x++) {
		Blocks[x][-101] = (Block::declareAndInit(GameObject::m_state, "", x, -101, Ceiling.random()));
		Blocks[x][-102] = (Block::declareAndInit(GameObject::m_state, "", x, -102, BackGround.random()));
		Blocks[x][-103] = (Block::declareAndInit(GameObject::m_state, "", x, -103, BackGround.random()));
		Blocks[x][-104] = (Block::declareAndInit(GameObject::m_state, "", x, -104, Ground.random()));
		Border[x] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0, 103.5f,
			0, +101.5);

	}

	/*
	* Create the entry points where enemies spawn in
	*/
	delete Blocks[-3][-101];
	delete Border[-3];
	Blocks[-3][-101] = (Block::declareAndInit(GameObject::m_state, "", -3, -101, BackGround.random()));
	for (int y = 1; y < 4; y++) {
		Blocks[-3][-101 + y] = (Block::declareAndInit(GameObject::m_state, "", -3, -101 +y, BackGround.random()));
		Blocks[-2][-101 + y] = (Block::declareAndInit(GameObject::m_state, "", -2, -101 + y, LeftWall.random()));
		Blocks[-4][-101 + y] = (Block::declareAndInit(GameObject::m_state, "", -4, -101 + y, RightWall.random()));
	}
	Border[-3] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0, +103.5,
		0, +0);
	/*
	* 
	* Second spawn point drop
	* 
	*/

	delete Blocks[+8][-101];
	delete Border[+8];
	Blocks[8][-101] = (Block::declareAndInit(GameObject::m_state, "", 8, -101, BackGround.random()));
	for (int y = 1; y < 4; y++) {
		Blocks[8][-101 + y] = (Block::declareAndInit(GameObject::m_state, "", 8, -101 + y, BackGround.random()));
		Blocks[7][-101 + y] = (Block::declareAndInit(GameObject::m_state, "", 7, -101 + y, RightWall.random()));
		Blocks[9][-101 + y] = (Block::declareAndInit(GameObject::m_state, "", 9, -101 + y, LeftWall.random()));
	}
	Border[8] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0, +103.5,
		0, +0);



	Blocks[15][-101] = (Block::declareAndInit(GameObject::m_state, "", 15, -101, BottomLeftEdge.random()));
	Blocks[15][-102] = (Block::declareAndInit(GameObject::m_state, "", 15, -102, LeftWall.random()));
	Blocks[15][-103] = (Block::declareAndInit(GameObject::m_state, "", 15, -103, LeftWall.random()));
	Blocks[15][-104] = (Block::declareAndInit(GameObject::m_state, "", 15, -104, UpperLeftEdge.random()));




	for (int x = -20; x < 30; x++) {
		fillLowerY(x, -99, 100);
		fillUpperY(x, -100, 120);
	}

	Boss* finalBoss = new Boss(GameObject::m_state);
	finalBoss->init(10, -102);
	GameObject::m_state->appendEntity(finalBoss);

}

void FinalBossDrawer::update(float dt) {
	Drawer::update(dt);
}

void FinalBossDrawer::draw() {
	Drawer::draw();
}

FinalBossDrawer::~FinalBossDrawer() {

}
