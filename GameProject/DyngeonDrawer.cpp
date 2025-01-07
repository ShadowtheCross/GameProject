#include "LevelBuilding.h"
#include "fstream"

#include <string>
#include "GameState.h"
#include "GameLogic.h"
#include "Config.h"
#include "BorderMapManagement.h"
#include "Miscallenious.h"

DungeonDrawer::DungeonDrawer(GameState* gs, std::string name) : Drawer(gs,name){

}

void DungeonDrawer::init(std::string constructionFile, std::string texturesFile,std::string TexturesPerBlock) {
	
	Drawer::init(constructionFile, texturesFile, TexturesPerBlock);

	// Load The brushes
	HalfBlockDown.setup(texturesFile + "HalfBlockDown", TexturesNum["HalfBlockDown"]);
	HalfCeilingDown.setup(texturesFile + "HalfCeilingDown", TexturesNum["HalfCeilingDown"]);
	HalfCeilingUp.setup(texturesFile + "HalfCeilingUp", TexturesNum["HalfCeilingUp"]);
	HalfBlockUp.setup(texturesFile + "HalfBlockUp", TexturesNum["HalfBlockUp"]);
	RightEdge.setup(texturesFile + "RightEdge", TexturesNum["RightEdge"]);
	LeftEdge.setup(texturesFile + "LeftEdge", TexturesNum["LeftEdge"]);
	BackGround.setup(texturesFile + "BackGround", TexturesNum["BackGround"]);
	Ceiling.setup(texturesFile + "Ceiling", TexturesNum["Ceiling"]);
	Ground.setup(texturesFile + "Ground", TexturesNum["Ground"]);
	GroundRight.setup( texturesFile + "GroundRight", TexturesNum["GroundRight"]);
	LeftWall.setup( texturesFile + "LeftWall", TexturesNum["LeftWall"]);
	RightWall.setup( texturesFile + "RightWall", TexturesNum["RightWall"]);
	UpperRightEdge.setup(texturesFile + "UpperRightEdge", TexturesNum["UpperRightEdge"]);
	UpperLeftEdge.setup(texturesFile + "UpperLeftEdge", TexturesNum["UpperLeftEdge"]);
	BottomRightEdge.setup(texturesFile + "BottomRightEdge", TexturesNum["BottomRightEdge"]);
	BottomLeftEdge.setup(texturesFile + "BottomLeftEdge", TexturesNum["BottomLeftEdge"]);

	std::ifstream file(constructionFile);
	std::string data,type,length;
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
		else if (type == "drawCavern") {
			drawCavern(n);
		}


		std::getline(file, data);
	}
	file.close();
	drawEnd();


}

void DungeonDrawer::update(float dt) {

}



void DungeonDrawer::drawStart() {
	//fill blank on the back
	for (int i = -30; i < -1 ;i++) {
		fillUpperY(i, -1, 20);
		fillLowerY(i, 0, 20);
	}


	//PathStart
	int BlockSize = GameObject::m_state->getBlockSize();

	//for the back wall
	fillUpperY(-1, 1, 20);
	fillLowerY(-1, -1, 20);
	Blocks[-1][-1]= (Block::declareAndInit(GameObject::m_state, "", -1, -1, UpperRightEdge.random()));
	Blocks[-1][0] = (Block::declareAndInit(GameObject::m_state, "",-1, 0, RightWall.random() ));
	Blocks[-1][1] = (Block::declareAndInit(GameObject::m_state, "", -1, 1, BottomRightEdge.random()));

	//for the starting point
	fillUpperY(0, +1, 20);
	fillLowerY(0, -1, 20);
	Blocks[0][0] = (Block::declareAndInit(GameObject::m_state, "", 0, 0, BackGround.random() ));
	Blocks[0][1] = (Block::declareAndInit(GameObject::m_state, "", 0, 1, Ceiling.random() ));
	Blocks[0][-1] = (Block::declareAndInit(GameObject::m_state, "",0, -1,Ground.random() ));
	


	Border[0] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, .5f, //bottom 
		0.0, -.5f); //top
	Chest* temp = new Chest(GameObject::m_state, "");
	temp->init(0, 0);

	GameObject::m_state->appendStaticEntity(temp);

	
	x_next = 1;
	y_next = 0;

}

void DungeonDrawer::drawLine(int n) {
	if (n < 0) {
		return;
	}
	int BlockSize = GameObject::m_state->getBlockSize();
	for (int i = 0; i < n; i++) {
		Blocks[x_next][y_next] = (EnemyBlock::declareAndInit(GameObject::m_state, "", x_next, y_next, BackGround.random(), Config::spawn_rate ));
		Blocks[x_next][y_next - 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, Ground.random() ));
		Blocks[x_next][y_next + 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 1, Ceiling.random() ));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, (-y_next + 0.5f) , 
			0.0, (-y_next - 0.5f) );
		fillUpperY(x_next, y_next+1, 20);
		fillLowerY(x_next, y_next-1, 20);
		x_next++;
	}
}

void DungeonDrawer::drawUpBlocks(int n) {
	n = n / 2;
	for (int i = 0; i < n; i++) {
		if (i % 2) {

		
		Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, HalfBlockUp.random()));
		Blocks[x_next][y_next +1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 1, HalfCeilingUp.random()));
		Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next-1, UpperLeftEdge.random()));
		Blocks[x_next][y_next +2] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 2, BottomRightEdge.random()));

		fillUpperY(x_next, y_next + 1, 20);
		fillLowerY(x_next, y_next, 20);

		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, (-y_next+0.2 ),
			0.0, (-y_next -1.2 ));
		x_next++;
		y_next++;
		}
		else {
			drawLine(5);
		}
	}
}

void DungeonDrawer::drawDownBlocks(int n) {
	n = n /2;
	for (int i = 0; i < n; i++) {
		if (i % 2) {
		Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, HalfCeilingDown.random()));
		Blocks[x_next][y_next - 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, HalfBlockDown.random()));
		Blocks[x_next][y_next+1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next+1, BottomLeftEdge.random()));
		Blocks[x_next][y_next - 2] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 2, UpperRightEdge.random()));

		fillUpperY(x_next, y_next , 20);
		fillLowerY(x_next, y_next - 1, 20);
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, (-y_next+1.2),
			0.0, (-y_next-0.2));
		x_next++;
		y_next--;
		}
		else {
			drawLine(5);
		}

		
		
		
	}
}



void DungeonDrawer::drawDropDown(int n) {
	//Draw the start
	int BlockSize = GameObject::m_state->getBlockSize();

	


	// x where the drop is
	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next, BackGround.random() ) );
	Blocks[x_next][y_next - 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, GroundRight.random() ));
	Blocks[x_next][y_next + 1] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next + 1, Ceiling.random() ));

	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, (-y_next + 0.5f),
		0.0, (-y_next - 0.5f));
	x_next++;

	//Above the wall on the right hand side

	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next, BackGround.random() ));
	Blocks[x_next+1][y_next + 1] = (Block::declareAndInit(GameObject::m_state, "", x_next+1 , y_next + 1, BottomLeftEdge.random()));

	Blocks[x_next][y_next + 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next+1, Ceiling.random() ));
	Blocks[x_next+1][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next + 1, y_next , LeftWall.random() ));
	
	y_next--;

	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, BackGround.random() ));
	Blocks[x_next+1][y_next] =(Block::declareAndInit(GameObject::m_state, "",x_next+1, y_next, LeftWall.random() ));
	y_next--;

	float temp_y = y_next + 3;
	for (int i = 0; i < n; i++) {
		Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, BackGround.random() ));
		Blocks[x_next - 1 ][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next-1, y_next , RightWall.random() ));
		Blocks[x_next + 1][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next+1, y_next , LeftWall.random() ));
		y_next--;
	}
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		-0.0f, (-y_next + 0.5),
		-0.0f, (-temp_y - 0.5)
	);

	//The end of the drop
	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next , BackGround.random() ));
	Blocks[x_next-1][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next -1 , y_next , RightWall.random() ) );
	Blocks[x_next - 1][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next - 1, y_next-1, UpperRightEdge.random()));
	Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next-1, Ground.random() ));
	x_next++;

	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, BackGround.random()));
	Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next-1, Ground.random()));
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		-0.0f, (-y_next + 0.5),
		-0.0f, (-y_next - 0.5)
	);

	x_next++;
	fillUpperY(x_next-1, y_next, 20);
	fillUpperY(x_next-2, y_next, 20);
	fillUpperY(x_next-3, y_next, 20);
	fillLowerY(x_next-1, y_next, 20);
	fillLowerY(x_next-2, y_next, 20);
	fillLowerY(x_next-3, y_next, 20);

	drawLine(1);

}
void DungeonDrawer::drawCavern(int n) {
	int BlockSize = GameObject::m_state->getBlockSize();
	
	Blocks[x_next][y_next] = (EnemyBlock::declareAndInit(GameObject::m_state, "", x_next, y_next, BackGround.random(), Config::spawn_rate));
	Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, Ground.random() ));
	Blocks[x_next][y_next+1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 1, LeftEdge.random() ));
	
	
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, -y_next + 0.5f,
		-1.0f, -y_next -1.0f);
	fillLowerY(x_next, y_next - 1, 20);
	fillUpperY(x_next, y_next + 1, 20);
	
	
	
	
	x_next++;
	for (int i = 0; i < n - 2; i++) {
		Blocks[x_next][y_next] = (EnemyBlock::declareAndInit(GameObject::m_state, "", x_next, y_next, BackGround.random(), Config::spawn_rate) );
		Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, Ground.random() ));
		Blocks[x_next][y_next+1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 1, BackGround.random() ));
		Blocks[x_next][y_next+2] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 2, Ceiling.random() ));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0f, (-y_next + .5f) ,
			0.0f, (-y_next - 1.5f) 
		);
		fillLowerY(x_next, y_next - 1, 20);
		fillUpperY(x_next, y_next + 2, 20);
		x_next++;
	}

	Blocks[x_next][y_next] =(EnemyBlock::declareAndInit(GameObject::m_state, "", x_next, y_next, BackGround.random(), Config::spawn_rate));
	Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next - 1, Ground.random() ));
	Blocks[x_next][y_next+1] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next + 1, RightEdge.random()));
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, -y_next + 0.5f,
		1.0f, -y_next - 1.0f);
	fillLowerY(x_next, y_next - 1, 20);
	fillUpperY(x_next, y_next + 1, 20);

	x_next++;

}




void DungeonDrawer::drawEnd() {
	int BlockSize = GameObject::m_state->getBlockSize();
	

	//PathStart
	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next, BackGround.random() ) );
	Blocks[x_next][y_next+1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next+1, Ceiling.random() ));
	Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next -1, Ground.random() ));
	Blocks[x_next+1][y_next] =(Block::declareAndInit(GameObject::m_state, "", x_next+1, y_next, LeftWall.random() ));
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		-0.0f, (-y_next + 0.5f) ,
		0.0f, (-y_next - 0.5f) 
	);
	//The exit x
	fillLowerY(x_next, y_next -1, 20);
	fillUpperY(x_next, y_next + 1, 20);
	//x at the right wall
	fillLowerY(x_next+1, y_next, 20);
	fillUpperY(x_next+1, y_next, 20);
	for (int i = 2; i < 20; i++) {
		//fill the rest
		fillLowerY(x_next+i, y_next, 20);
		fillUpperY(x_next+i, y_next-1, 20);
	}


	Door* test = new Door(GameObject::m_state, "");
	test->init(x_next, y_next);
	GameObject::m_state->appendStaticEntity(test);
	

}

void DungeonDrawer::draw() {
	Drawer::draw();
	

}
DungeonDrawer::~DungeonDrawer() {
	
}