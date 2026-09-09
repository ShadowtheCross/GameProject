#include "LevelBuilding.h"

Drawer::Drawer(GameState *gs, std::string name) : GameObject(gs,name) {

}

void Drawer::drawStart() {}
void Drawer::drawEnd() {}

void Drawer::addBlock(int x, int y, graphics::Brush * br) {
	if (Blocks[x][y] == nullptr) {
		Blocks[x][y] = Block::declareAndInit(GameObject::m_state, "", x, y, br);
	}
	else {
		Block* temp = Blocks[x][y];
		delete temp;
		Blocks[x][y] = Block::declareAndInit(GameObject::m_state, "", x, y, br);
	}
}

void Drawer::addEnemyBlock(int x, int y, graphics::Brush* br) {
	if (Blocks[x][y] == nullptr) {
		Blocks[x][y] = EnemyBlock::declareAndInit(GameObject::m_state, "", x, y, br,Config::spawn_rate);
	}
	else {
		Block* temp = Blocks[x][y];
		delete temp;
		Blocks[x][y] = EnemyBlock::declareAndInit(GameObject::m_state, "", x, y, br, Config::spawn_rate);
	}
}


void Drawer::drawExit(int x,int y) {
	ExitDoor* temp = new ExitDoor(GameObject::m_state);
	temp->init(x, y);
	GameObject::m_state->appendStaticEntity(temp);

}
void Drawer::drawChest(int x,int y) {
	Chest* temp = new Chest(GameObject::m_state, "Chest");
	temp->init(x, y);
	GameObject::m_state->appendStaticEntity(temp);
}


void Drawer::init(std::string constructionFile, std::string texturesFile, std::string TexturesPerBlock) {
	loadTexturesPerNum(TexturesPerBlock);
	OutsideMap.setup(texturesFile + "OutsideMap", TexturesNum["OutsideMap"]);
	GameObject::m_state->setBorder(&Border);
	GameObject::m_state->setAgro(false);

}

void Drawer::draw() {
	int start_x, end_x, start_y, end_y;
	int gx = GameObject::m_state->getGlobalX();
	int gy = GameObject::m_state->getGlobalY();
	int BlockSize = GameObject::m_state->getBlockSize();

	int cx = -(gx - Config::window_width / 2) / BlockSize;
	int cy = (gy - Config::window_height / 2) / BlockSize;
	for (int x = cx - 10; x < cx + 10; x++) {
		for (int y = cy - 10; y < cy + 10; y++) {
			if (Blocks[x][y]) {
				Blocks[x][y]->draw();
			}
		}
	}
}

void Drawer::update(float dt) {

}

void Drawer::loadTexturesPerNum(std::string file) {
	std::ifstream textures(file);
	std::string line, Texture, value;
	while (textures.good()) {
		std::getline(textures, line);
		doubleDotSplit(line, Texture, value);
		TexturesNum[Texture] = stoi(value);
	}
}

void Drawer::fillUpperY(int x_next, int y_next, int nBlocks) {
	int top =  y_next + 1 + nBlocks;
	for (int i = y_next + 1; i < top; i++) {
		if (Blocks[x_next][i] == nullptr) 
		Blocks[x_next][i] = (Block::declareAndInit(GameObject::m_state, "", x_next, i, OutsideMap.random()));
	}

}
void Drawer::fillLowerY(int x_next, int y_next, int nBlocks) {
	int Bottom = y_next - 1 - nBlocks;
	for (int i = y_next - 1; i  > Bottom; i--) {
		if (Blocks[x_next][i] == nullptr) 
		Blocks[x_next][i] = (Block::declareAndInit(GameObject::m_state, "", x_next, i, OutsideMap.random()));
	}
}


Drawer::~Drawer() {
	for (auto& x : Blocks) {
		for (auto& y : x.second) {
			delete y.second;
		}
		x.second.clear();
	}
	Blocks.clear();
}