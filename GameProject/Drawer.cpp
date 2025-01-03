#include "LevelBuilding.h"
#include "fstream"

#include <string>
#include "GameState.h"
#include "GameLogic.h"
#include "Config.h"
#include "BorderMapManagement.h"
#include "Miscallenious.h"

DungeonDrawer::DungeonDrawer(GameState* gs, std::string name) : GameObject(gs,name){

}

void DungeonDrawer::init(std::string constructionFile, std::string texturesFile,std::string TexturesPerBlock) {
	
	loadTexturesPerNum(TexturesPerBlock);


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

	GameObject::m_state->setBorder(&Border);

}

void DungeonDrawer::update(float dt) {

}

void DungeonDrawer::loadTexturesPerNum(std::string file) {
	std::ifstream textures(file);
	std::string line, Texture, value;
	while (textures.good()) {
		std::cout << line  <<std::endl;
		std::getline(textures, line);
		doubleDotSplit(line,Texture,value );
		TexturesNum[Texture] = stoi(value);
	}
}


void DungeonDrawer::drawStart() {
	//PathStart
	int BlockSize = GameObject::m_state->getBlockSize();
	Blocks[0][0] = (Block::declareAndInit(GameObject::m_state, "", 0, 0, BackGround.random() ));
	Blocks[0][1] = (Block::declareAndInit(GameObject::m_state, "", 0, 1, Ceiling.random() ));
	Blocks[0][-1] = (Block::declareAndInit(GameObject::m_state, "",0, -1,Ground.random() ));
	Blocks[-1][0] = (Block::declareAndInit(GameObject::m_state, "",-1, 0, RightWall.random() ));
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
		x_next++;
	}
}

void DungeonDrawer::drawUpBlocks(int n) {
	n = n - n % 2;
	for (int i = 0; i < n; i++) {
		if (i % 2) {

		
		Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, HalfBlockUp.random()));
		Blocks[x_next][y_next +1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 1, HalfCeilingUp.random()));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, (-y_next ),
			0.0, (-y_next -1 ));
		x_next++;
		y_next++;
		}
		else {
			drawLine(2);
		}
	}
}

void DungeonDrawer::drawDownBlocks(int n) {
	n = n - n % 2;
	for (int i = 0; i < n; i++) {
		if (i % 2) {
		Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, HalfCeilingDown.random()));
		Blocks[x_next][y_next - 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, HalfBlockDown.random()));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, (-y_next + 1),
			0.0, (-y_next));
		x_next++;
		y_next--;
		}
		else {
			drawLine(2);
		}

		
		
		
	}
}



void DungeonDrawer::drawDropDown(int n) {
	//Draw the start
	int BlockSize = GameObject::m_state->getBlockSize();

	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next, BackGround.random() ) );
	Blocks[x_next][y_next - 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, GroundRight.random() ));
	Blocks[x_next][y_next + 1] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next + 1, Ceiling.random() ));
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, (y_next + 0.5) ,
		0.0, (y_next - 0.5) 
		);
	x_next++;


	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next, BackGround.random() ));
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


	Blocks[x_next][y_next] =(Block::declareAndInit(GameObject::m_state, "", x_next, y_next , BackGround.random() ));
	Blocks[x_next-1][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next -1 , y_next , RightWall.random() ) );
	Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next-1, Ground.random() ));
	x_next++;
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
		
		x_next++;
	}

	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, -y_next + 0.5f,
		1.0f, -y_next - 1.0f);


	Blocks[x_next][y_next] =(EnemyBlock::declareAndInit(GameObject::m_state, "", x_next, y_next, BackGround.random(), Config::spawn_rate));
	Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next - 1, Ground.random() ));
	Blocks[x_next][y_next+1] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next + 1, RightEdge.random()));
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
	Door* test = new Door(GameObject::m_state, "");
	test->init(x_next, y_next);
	GameObject::m_state->appendStaticEntity(test);
	

}

void DungeonDrawer::draw() {
	int start_x, end_x, start_y, end_y;
	int gx = GameObject::m_state->getGlobalX();
	int gy = GameObject::m_state->getGlobalY();
	int BlockSize = GameObject::m_state->getBlockSize();

	int cx = -(gx - Config::window_width / 2) / BlockSize;
	int cy = (gy - Config::window_height / 2) / BlockSize;
	for (int x = cx-10; x < cx+10; x++) {
		for (int y = cy-10; y < cy+10; y++) {
			if (Blocks[x][y]) {
				Blocks[x][y]->draw();
			}
		}
	}
	

}
DungeonDrawer::~DungeonDrawer() {
	for (auto& x : Blocks) {
		for (auto& y : x.second) {
			delete y.second;
		}
	}

}