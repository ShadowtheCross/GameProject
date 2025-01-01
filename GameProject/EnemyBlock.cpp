#include "LevelBuilding.h"
#include "Miscallenious.h"


EnemyBlock::EnemyBlock(GameState* gs, std::string name) : Block(gs, name) {

}

void EnemyBlock::init(float x_cord, float y_cord, graphics::Brush* toUse, int spawnRate) {
	Block::init(x_cord, y_cord, toUse);
	
	if (spawnRate > randomInt(1, 100) ) {

		//Spawn Enemy
		if (randomInt(0, 1) ) {
			GameObject::m_state->appendEntity(Goblin::declareAndInit(GameObject::m_state, x_cord, y_cord));
		}
		else {
			GameObject::m_state->appendEntity(Skeleton::declareAndInit(GameObject::m_state, x_cord, y_cord));
		}
	}
}

EnemyBlock* EnemyBlock::declareAndInit(GameState* gs, std::string name, int x_cord, int y_cord, graphics::Brush* toUse, int rate) {
	EnemyBlock* temp = new EnemyBlock(gs, name);
	temp->init(x_cord, y_cord, toUse, rate);
	return temp;
}

void EnemyBlock::draw() {
	Block::draw();
}
void EnemyBlock::update() {
	Block::update();
}
EnemyBlock::~EnemyBlock() {

}