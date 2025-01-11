#include "LevelBuilding.h"

FinalOpenMapDrawer::FinalOpenMapDrawer(GameState *gs,std::string name) : OpenMapDrawer(gs,name) {
	
}

void FinalOpenMapDrawer::init(std::string constructionFile, std::string texturesFile, std::string TexturesPerBlock) {
	OpenMapDrawer::init(constructionFile, texturesFile, TexturesPerBlock);
}

void FinalOpenMapDrawer::drawExit(int x,int y) {
	DecorativeDoor* d = new DecorativeDoor(GameObject::m_state, "Deadly Door");
	d->init(x_next, y_next);
	GameObject::m_state->appendStaticEntity(d);
}


void FinalOpenMapDrawer::draw() {
	OpenMapDrawer::draw();
}
void FinalOpenMapDrawer::update(float dt) {
	OpenMapDrawer::update(dt);
	
	if (!fallTrigger && abs(GameObject::m_state->getPlayerX() - x_next) < .1f) {
		fallTrigger = true;
		levelTrigger = true;
		Block* tempBlock;
		BlockBorder* tempBorder;
		tempBorder = Border[x_next];
		delete  tempBorder;
		Border[x_next] = BlockBorder::buildAndInit(GameObject::m_state, "",
			0, -y_next + 105.0f,
			0, -y_next - 0.5f);


		//Create and render drop
		tempBlock = Blocks[x_next][y_next - 1];
		delete tempBlock;
		Blocks[x_next][y_next - 1] = Block::declareAndInit(GameObject::m_state, "",
			x_next, y_next - 1, BackGround.random());
		y_next -= 2;
		for (int i = 0; i < 200; i++) {
			if (Blocks[x_next][y_next] != nullptr) {
				tempBlock = Blocks[x_next][y_next];
				delete tempBlock;
			}
			Blocks[x_next][y_next] = Block::declareAndInit(GameObject::m_state, "", x_next, y_next, BackGround.random());
			y_next--;
		}
		trigger_y = y_next + 200;
	}
	
	
	if (fallTrigger && levelTrigger) {
		int change_y = GameObject::m_state->getPlayerY() + trigger_y;
		if (abs(change_y) < 1) {
			GameObject::m_state->nextLevel();
			levelTrigger = false;
		}
	}
	


}




FinalOpenMapDrawer::~FinalOpenMapDrawer() {

}