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
		0, -9.5);
	Border[-1] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0, 103.5f,
		0, +100.5);
	Border[+1] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0, 103.5f,
		0, +100.5);


	//draw the arena
	for (int x = -5; x < -1; x++) {
		Blocks[x][-101] = (Block::declareAndInit(GameObject::m_state, "", x, -101, Ceiling.random()));
		Blocks[x][-102] = (Block::declareAndInit(GameObject::m_state, "", x, -102, BackGround.random()));
		Blocks[x][-103] = (Block::declareAndInit(GameObject::m_state, "", x, -103, BackGround.random()));
		Blocks[x][-104] = (Block::declareAndInit(GameObject::m_state, "", x, -103, Ground.random()));
		Border[0] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0, 104.5f,
			0, -9.5);
	}
	for (int x = 2; x < 15; x++) {
		Blocks[x][-101] = (Block::declareAndInit(GameObject::m_state, "", x, -101, Ceiling.random()));
		Blocks[x][-102] = (Block::declareAndInit(GameObject::m_state, "", x, -102, BackGround.random()));
		Blocks[x][-103] = (Block::declareAndInit(GameObject::m_state, "", x, -103, BackGround.random()));
		Blocks[x][-104] = (Block::declareAndInit(GameObject::m_state, "", x, -103, Ground.random()));
		Border[0] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0, 104.5f,
			0, -9.5);

	}




}

void FinalBossDrawer::update(float dt) {
	Drawer::update(dt);
}

void FinalBossDrawer::draw() {
	Drawer::draw();
}

FinalBossDrawer::~FinalBossDrawer() {

}
