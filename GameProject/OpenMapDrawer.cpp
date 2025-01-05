#include "LevelBuilding.h"

OpenMapDrawer::OpenMapDrawer(GameState*gs,std::string name) : Drawer(gs,name) {
}

void OpenMapDrawer::init(std::string constructionFile, std::string texturesFile, std::string TexturesPerBlock) {
	Drawer::init(constructionFile, texturesFile, TexturesPerBlock);
	BackGround.setup(texturesFile + "BackGround", TexturesNum["BackGround"]);
	RightWall.setup(texturesFile + "RightWall", TexturesNum["RightWall"]);
	LeftWall.setup(texturesFile + "LeftWall", TexturesNum["LeftWall"]);
	Ground.setup(texturesFile + "Ground", TexturesNum["Ground"]);
	Ceiling.setup(texturesFile + "Ceiling", TexturesNum["Ceiling"]);
	UpperRightEdge.setup(texturesFile + "UpperRightEdge", TexturesNum["UpperRightEdge"]);
	UpperLeftEdge.setup(texturesFile + "UpperLeftEdge", TexturesNum["UpperLeftEdge"]);
	BottomRightEdge.setup(texturesFile + "BottomRightEdge", TexturesNum["BottomRightEdge"]);
	BottomLeftEdge.setup(texturesFile + "BottomLeftEdge", TexturesNum["BottomLeftEdge"]);
	HalfBlock.setup(texturesFile + "HalfBlock", TexturesNum["HalfBlock"]);
	std::ifstream file(constructionFile);
	std::string data, type, length;
	std::getline(file, data);
	int n;


	drawStart();
	while (file.good()) {
		doubleDotSplit(data, type, length);
		n = stoi(length);
		if (type == "drawLine") {
			drawLine(n);
		}
		else if (type == "drawDownBlocks") {
			drawDownBlocks(n);
		}
		else if (type == "drawUpBlocks") {
			drawUpBlocks(n);
		}
		else if (type == "drawDropDown") {
		//	drawDropDown(n);
		}
		else if (type == "drawSpikeDrop") {
			drawSpikeDrop(n);
		}


		std::getline(file, data);
	}
	file.close();
	drawEnd();

}

void OpenMapDrawer::update(float dt) {

}

void OpenMapDrawer::draw() {
	Drawer::draw();
}

OpenMapDrawer::~OpenMapDrawer() {

}

void OpenMapDrawer::drawStart() {
	for (int i = -30; i < -1; i++) {
		fillUpperY(i, -1, 20);
		fillLowerY(i, 0, 20);
	}

	//PathStart
	int BlockSize = GameObject::m_state->getBlockSize();

	//for the back wall
	fillUpperY(-1, 1, 20);
	fillLowerY(-1, -1, 20);
	Blocks[-1][-1] = (Block::declareAndInit(GameObject::m_state, "", -1, -1, UpperRightEdge.random()));
	Blocks[-1][0] = (Block::declareAndInit(GameObject::m_state, "", -1, 0, RightWall.random()));
	Blocks[-1][1] = (Block::declareAndInit(GameObject::m_state, "", -1, 1, BottomRightEdge.random()));

	//for the starting point
	x_next = 0;
	y_next = 0;
	while (x_next < 20) {
		fillUpperY(x_next, +1, 20);
		fillLowerY(x_next, -1, 20);
		Blocks[x_next][0] = (Block::declareAndInit(GameObject::m_state, "", x_next, 0, BackGround.random()));
		Blocks[x_next][1] = (Block::declareAndInit(GameObject::m_state, "", x_next, 1, Ceiling.random()));
		Blocks[x_next][-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, -1, Ground.random()));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, .5f, //bottom 
			0.0, -.5f); //top
		x_next++;
	}
	drawLine(1);
}


void OpenMapDrawer::drawLine(int n) {

	for (int i = 0; i < n; i++) {
		Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next-1 , Ground.random()));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, -y_next+.5f, //bottom 
			0.0, -y_next-top); //top
		fillLowerY(x_next, y_next , 20);
		x_next++;
	}

}

void OpenMapDrawer::drawUpBlocks(int n) {

	for (int i = 0; i < n / 2; i++) {
		Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, HalfBlock.random()));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, -y_next, //bottom 
			0.0, -y_next - top); //top
		fillLowerY(x_next, y_next, 20);
		y_next++;
		x_next++;
		drawLine(1);
	}

}

void OpenMapDrawer::drawDownBlocks(int n) {
	for (int i = 0; i < n / 2; i++) {
		y_next--;
		Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, HalfBlock.random()));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, -y_next, //bottom 
			0.0, -y_next - top); //top
		fillLowerY(x_next, y_next, 20);
		x_next++;
		drawLine(1);

	}

}


void OpenMapDrawer::drawSpikeDrop(int n) {
	for (int i = 0; i < n; i++) {
	//Draw Ledge
	Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next-1, Ground.random()));
	Blocks[x_next][y_next-2] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 2, LeftWall.random()));
	Blocks[x_next][y_next-3] = Blocks[x_next][y_next-3] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 3, UpperRightEdge.random()));
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, -y_next + 0.5, //bottom 
		0.0, -y_next - top);
	fillLowerY(x_next, y_next, 20);


	x_next++;
	//Draw the drop
	Blocks[x_next][y_next - 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, BackGround.random()));
	Blocks[x_next][y_next - 2] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 2, BackGround.random()));
	Blocks[x_next][y_next - 3] = Blocks[x_next][y_next - 3] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 3, Ground.random()));
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, -y_next + 2.5, 
		0.0, -y_next - top);
	fillLowerY(x_next, y_next-2, 20);
	x_next++;

	//draw the next edge
	Blocks[x_next][y_next - 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, Ground.random()));
	Blocks[x_next][y_next - 2] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 2, RightWall.random()));
	Blocks[x_next][y_next - 3] = Blocks[x_next][y_next - 3] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 3, UpperLeftEdge.random()));
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, -y_next + 0.5, //bottom 
		0.0, -y_next - top);
	fillLowerY(x_next, y_next, 20);
	x_next++;
	}
	
}



void OpenMapDrawer::drawEnd() {
	int BlockSize = GameObject::m_state->getBlockSize();


	//Cave Exit
	for (int i = 0; i < 10; i++) {
		Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, BackGround.random()));
		Blocks[x_next][y_next + 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 1, Ceiling.random()));
		Blocks[x_next][y_next - 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, Ground.random()));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			-0.0f, (-y_next + 0.5f),
			0.0f, (-y_next - 0.5f));
		fillLowerY(x_next, y_next - 1, 20);
		fillUpperY(x_next, y_next + 1, 20);
		x_next++;
	}
	//Exit
	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, BackGround.random()));
	Blocks[x_next][y_next + 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 1, Ceiling.random()));
	Blocks[x_next][y_next - 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, Ground.random()));
	
	//End
	Blocks[x_next + 1][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next + 1, y_next, RightWall.random()));
	Blocks[x_next + 1][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next + 1, y_next-1, UpperLeftEdge.random()));
	Blocks[x_next + 1][y_next+1] = (Block::declareAndInit(GameObject::m_state, "", x_next + 1, y_next+1, BottomLeftEdge.random()));
	
	/*
	* 
	* Door to exit
	* 
	*/
	Door* test = new Door(GameObject::m_state, "");
	test->init(x_next, y_next);
	GameObject::m_state->appendStaticEntity(test);

	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		-0.0f, (-y_next + 0.5f),
		0.0f, (-y_next - 0.5f)
	);




	//The exit x
	fillLowerY(x_next, y_next - 1, 20);
	fillUpperY(x_next, y_next + 1, 20);
	//x at the right wall
	fillLowerY(x_next + 1, y_next, 20);
	fillUpperY(x_next + 1, y_next, 20);
	for (int i = 2; i < 20; i++) {
		//fill the rest
		fillLowerY(x_next + i, y_next, 20);
		fillUpperY(x_next + i, y_next - 1, 20);
	}



}

