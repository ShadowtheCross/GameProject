#include "LevelBuilding.h"
#include "fstream"

#include <string>
#include "GameState.h"
#include "GameLogic.h"
#include "Config.h"
#include "BorderMapManagement.h"
#include "Miscallenious.h"

Drawer::Drawer(GameState* gs, std::string name) : GameObject(gs,name){

}

void Drawer::init(std::string constructionFile, std::string texturesFile) {

	// Load The brushes

	BackGround.outline_opacity = 0.0f;
	BackGround.texture = texturesFile + "BackGround.png";
	Ceiling.outline_opacity = 0.0f;
	Ceiling.texture = texturesFile + "Ceiling.png";
	DownStairs.outline_opacity = 0.0f;
	DownStairs.texture = texturesFile + "DownStairs.png";
	DownStairsCeiling.outline_opacity = 0.0f;
	DownStairsCeiling.texture = texturesFile + "DownStairsCeiling.png";
	Ground.outline_opacity = 0.0f;
	Ground.texture = texturesFile + "Ground.png";
	GroundRight.outline_opacity = 0.0f;
	GroundRight.texture = texturesFile + "GroundRight.png";
	LeftWall.outline_opacity = 0.0f;
	LeftWall.texture = texturesFile + "LeftWall.png";
	OutsideMap.outline_opacity = 0.0f;
	OutsideMap.texture = texturesFile + "OutsideMap.png";
	RightWall.outline_opacity = 0.0f;
	RightWall.texture = texturesFile + "RightWall.png";
	UpStairs.outline_opacity = 0.0f;
	UpStairs.texture = texturesFile + "UpStairs.png";
	UpStairsCeiling.outline_opacity = 0.0f;
	UpStairsCeiling.texture = texturesFile + "UpStairsCeilng.png";

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
		else if (type == "drawUpStairs") {
			drawUpStairs(n);
		}
		else if (type == "drawDownStairs") {
			drawDownStairs(n);
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

void Drawer::update() {

}

void Drawer::drawStart() {
	//PathStart
	int BlockSize = GameObject::m_state->getBlockSize();
	Blocks[0][0] = (Block::declareAndInit(GameObject::m_state, "", 0, 0, &BackGround));
	Blocks[0][1] = (Block::declareAndInit(GameObject::m_state, "", 0, 1, &Ceiling));
	Blocks[0][-1] = (Block::declareAndInit(GameObject::m_state, "",0, -1, &Ground));
	Blocks[-1][0] = (Block::declareAndInit(GameObject::m_state, "",-1, 0, &RightWall));
	Border[0] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, .5f, //bottom 
		0.0, -.5f); //top
	
	x_next = 1;
	y_next = 0;

}

void Drawer::drawLine(int n) {
	if (n < 0) {
		return;
	}
	int BlockSize = GameObject::m_state->getBlockSize();
	for (int i = 0; i < n; i++) {
		Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, &BackGround));
		Blocks[x_next][y_next - 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, &Ground));
		Blocks[x_next][y_next + 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 1, &Ceiling));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0, (-y_next + 0.5f) , 
			0.0, (-y_next - 0.5f) );
		x_next++;
	}
}

void Drawer::drawUpStairs(int n) {
	int BlockSize = GameObject::m_state->getBlockSize();

	for (int i = 0; i < n; i++) {
		
		Blocks[x_next][y_next] =(Block::declareAndInit(GameObject::m_state, "", x_next, y_next, &UpStairs));
		Blocks[x_next][y_next+1] =(Block::declareAndInit(GameObject::m_state, "",x_next, y_next+1, &UpStairsCeiling));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			-1.0, (-y_next ),
			-1.0, (-y_next - 1.0));
		x_next++;
		y_next++;
	}
}
void Drawer::drawDownStairs(int n) {
	int BlockSize = GameObject::m_state->getBlockSize();

	for (int i = 0; i < n; i++) {
		Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, &DownStairsCeiling));
		Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, &DownStairs));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			1.0, (-y_next+1),
			1.0, (-y_next) 
		);
		x_next++;
		y_next--;
	}
}
void Drawer::drawDropDown(int n) {
	//Draw the start
	int BlockSize = GameObject::m_state->getBlockSize();

	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next, &BackGround));
	Blocks[x_next][y_next - 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, &GroundRight));
	Blocks[x_next][y_next + 1] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next + 1, &Ceiling));
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, (y_next + 0.5) ,
		0.0, (y_next - 0.5) 
		);
	x_next++;

	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next, &BackGround));
	Blocks[x_next][y_next + 1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next+1, &Ceiling));
	Blocks[x_next+1][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next + 1, y_next , &LeftWall));	
	y_next--;

	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, &BackGround));
	Blocks[x_next+1][y_next] =(Block::declareAndInit(GameObject::m_state, "",x_next+1, y_next, &LeftWall));
	y_next--;
	
	for (int i = 0; i < n; i++) {
		Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next, &BackGround));
		Blocks[x_next - 1 ][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next-1, y_next , &RightWall));
		Blocks[x_next + 1][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next+1, y_next , &LeftWall));
		y_next--;
	}
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		-0.0f, (-y_next + n-3.5),
		-0.0f, (-y_next - 2*n+1.5)
	);


	Blocks[x_next][y_next] =(Block::declareAndInit(GameObject::m_state, "", x_next, y_next , &BackGround));
	Blocks[x_next-1][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next -1 , y_next , &RightWall));
	Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next-1, &Ground));
	x_next++;
	drawLine(1);

}
void Drawer::drawCavern(int n) {
	int BlockSize = GameObject::m_state->getBlockSize();
	
	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next , &BackGround));
	Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, &Ground));
	Blocks[x_next][y_next+1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 1, &UpStairsCeiling));
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		0.0, y_next + 0.5f,
		-1.0f, y_next -1.0f);
	
	
	
	
	
	
	x_next++;
	for (int i = 0; i < n - 2; i++) {
		Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next, &BackGround));
		Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next - 1, &Ground));
		Blocks[x_next][y_next+1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 1, &BackGround));
		Blocks[x_next][y_next+2] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next + 2, &Ceiling));
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0.0f, (y_next + .5f) ,
			0.0f, (y_next - 1.5f) 
		);
		
		x_next++;
	}

	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		-1.0f, (y_next + 1.0f) ,
		0.0f, (y_next - 0.5f)
	);

	Blocks[x_next][y_next] =(Block::declareAndInit(GameObject::m_state, "", x_next, y_next, &BackGround));
	Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next - 1, &Ground));
	Blocks[x_next][y_next+1] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next + 1, &DownStairsCeiling));
	x_next++;

}




void Drawer::drawEnd() {
	int BlockSize = GameObject::m_state->getBlockSize();


	//PathStart
	Blocks[x_next][y_next] = (Block::declareAndInit(GameObject::m_state, "",x_next, y_next, &BackGround));
	Blocks[x_next][y_next+1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next+1, &Ceiling));
	Blocks[x_next][y_next-1] = (Block::declareAndInit(GameObject::m_state, "", x_next, y_next -1, &Ground));
	Blocks[x_next+1][y_next] =(Block::declareAndInit(GameObject::m_state, "", x_next+1, y_next, &LeftWall));
	Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
		-0.0f, (-y_next + 0.5f) ,
		0.0f, (-y_next - 0.5f) 
	);


}

void Drawer::draw() {
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
Drawer::~Drawer() {
	

}