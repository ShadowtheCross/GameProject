#include "LevelBuilding.h"

OpenMapDrawer::OpenMapDrawer(GameState*gs,std::string name) : Drawer(gs,name) {
	backPanel = new VisualBackground(gs);
}

void OpenMapDrawer::init(std::string constructionFile, std::string texturesFile, std::string TexturesPerBlock) {
	Drawer::init(constructionFile, texturesFile, TexturesPerBlock);
	backPanel->init(1.5f,3.0f,texturesFile + "Back\\BackGround.png");

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
	DecorativeObjects.setup(texturesFile + "DecorativeObjects", TexturesNum["DecorativeObjects"]);
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
			drawDropDown(n);
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
	backPanel->update(dt);
}

void OpenMapDrawer::draw() {
	backPanel->draw();
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
	addBlock(-1, -1, UpperRightEdge.random());
	addBlock(-1, 0, LeftWall.random());
	addBlock(-1, 1, BottomRightEdge.random());

	//for the starting point
	x_next = 0;
	y_next = 0;
	while (x_next < 4) {
		fillUpperY(x_next, +1, 20);
		fillLowerY(x_next, -1, 20);
		addBlock(x_next ,  0, BackGround.random());
		addBlock(x_next , 1, Ceiling.random());
		addBlock(x_next , -1, Ground.random());
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, .5f, //bottom 
			0.0, -.5f); //top
		x_next++;
	}
	drawLine(1);
}


void OpenMapDrawer::drawLine(int n) {

	for (int i = 0; i < n; i++) {
		addBlock(x_next, y_next-1, Ground.random());
		addEnemyBlock(x_next, y_next, DecorativeObjects.random());
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, -y_next+.5f, //bottom 
			0.0, -y_next-top); //top
		fillLowerY(x_next, y_next , 20);
		x_next++;
	}

}

void OpenMapDrawer::drawUpBlocks(int n) {

	for (int i = 0; i < n / 2; i++) {
		addBlock(x_next, y_next, HalfBlock.random());
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, -y_next, //bottom 
			0.0, -y_next - top); //top
		fillLowerY(x_next, y_next, 20);
		y_next++;
		x_next++;
		drawLine(5);
	}

}

void OpenMapDrawer::drawDownBlocks(int n) {
	for (int i = 0; i < n / 2; i++) {
		y_next--;
		addBlock(x_next, y_next, HalfBlock.random());
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, -y_next, //bottom 
			0.0, -y_next - top); //top
		fillLowerY(x_next, y_next, 20);
		x_next++;
		drawLine(4);

	}

}


void OpenMapDrawer::drawSpikeDrop(int n) {
	Spikes* temp;
	for (int i = 0; i < n; i++) {
	//Draw Ledge
	addBlock(x_next, y_next, DecorativeObjects.random());
	addBlock(x_next, y_next-1, Ground.random());
	addBlock(x_next, y_next-2, LeftWall.random());
	addBlock(x_next, y_next-3, UpperRightEdge.random());
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, -y_next + 0.5, //bottom 
		0.0, -y_next - top);
	fillLowerY(x_next, y_next, 20);


	x_next++;
	//Draw the drop
	addBlock(x_next, y_next - 1, BackGround.random());
	addBlock(x_next, y_next - 2, BackGround.random());
	addBlock(x_next, y_next - 3, Ground.random());
	temp = new Spikes(GameObject::m_state);
	temp->init(x_next, y_next-2);
	GameObject::m_state->appendStaticEntity(temp);
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, -y_next + 2.5, 
		0.0, -y_next - top);
	fillLowerY(x_next, y_next-2, 20);
	x_next++;

	//draw the next edge
	addBlock(x_next, y_next, DecorativeObjects.random());
	addBlock(x_next, y_next - 1, Ground.random());
	addBlock(x_next, y_next - 2, RightWall.random());
	addBlock(x_next, y_next - 3, UpperLeftEdge.random());
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, -y_next + 0.5, //bottom 
		0.0, -y_next - top);
	fillLowerY(x_next, y_next, 20);
	x_next++;
	}
}

void OpenMapDrawer::drawDropDown(int n) {
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state,"",
		0, -y_next + 0.5,
		0, -y_next - top);
	addBlock(x_next, y_next - 1, Ground.random());
	y_next--;
	for (int i = 0; i < n; i++) {
		addBlock(x_next, y_next - 1, LeftWall.random());
		y_next--;
	}
	fillLowerY(x_next, y_next, 20);

	x_next++;
	drawLine(5);
}



void OpenMapDrawer::drawEnd() {
	int BlockSize = GameObject::m_state->getBlockSize();


	//Cave Exit
	for (int i = 0; i < 4; i++) {
		addBlock(x_next, y_next , BackGround.random());
		addBlock(x_next, y_next + 1, Ceiling.random());
		addBlock(x_next, y_next - 1, Ground.random());
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			-0.0f, (-y_next + 0.5f),
			0.0f, (-y_next - 0.5f));
		fillLowerY(x_next, y_next - 1, 20);
		fillUpperY(x_next, y_next + 1, 20);
		x_next++;
	}
	//Exit
	addBlock(x_next, y_next, BackGround.random());
	addBlock(x_next, y_next + 1, Ceiling.random());
	addBlock(x_next, y_next - 1, Ground.random());
	
	//End
	addBlock(x_next+1, y_next, RightWall.random());
	addBlock(x_next+1, y_next + 1, BottomLeftEdge.random());
	addBlock(x_next+1, y_next - 1, UpperLeftEdge.random());

	
	/*
	* 
	* DecorativeDoor to exit
	* 
	*/
	drawChest(x_next - 2, y_next);
	drawExit(x_next, y_next);
	
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		-0.0f, (-y_next + 0.5f),
		0.0f, (-y_next - 0.5f)
	);




	//The exit x
	fillLowerY(x_next, y_next - 1, 200);
	fillUpperY(x_next, y_next + 1, 200);
	//x at the right wall
	fillLowerY(x_next + 1, y_next, 200);
	fillUpperY(x_next + 1, y_next, 200);
	for (int i = -10; i < 0; i++) {
		fillLowerY(x_next + i, y_next - 1, 200);
	}

	for (int i = 0; i < 20; i++) {
		//fill the rest
		fillLowerY(x_next + i, y_next, 200);
		fillUpperY(x_next + i, y_next - 1, 200);
	}



}


void OpenMapDrawer::drawExit(int x, int y) {
	Drawer::drawExit(x, y);
}

