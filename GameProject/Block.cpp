#pragma once
#include "LevelBuilding.h"
#include "sgg/graphics.h"
#include "GameState.h"



Block::Block(GameState* gs, std::string name) : GameObject(gs,name ){

}

Block* Block::declareAndInit(GameState* gs, std::string name,  int x_cord, int y_cord, graphics::Brush* toUse) {
	Block* temp = new Block(gs, name);
	temp->init(x_cord,y_cord, toUse);
	return temp;

}

void Block::init(float x_cord, float y_cord, graphics::Brush* toUse) {
	x = x_cord;
	y = y_cord;
	b = toUse;
}

void Block::draw() {
	int BlockSize = GameObject::m_state->getBlockSize();
	float trueX = x*BlockSize + (GameObject::m_state->getGlobalX());
	float trueY = -y*BlockSize + (GameObject::m_state->getGlobalY());
	graphics::drawRect(trueX, trueY, BlockSize, BlockSize, *b);
}
void Block::drawDebug() {
	int BlockSize = GameObject::m_state->getBlockSize();
	float trueX = x * BlockSize + (GameObject::m_state->getGlobalX());
	float trueY = -y * BlockSize + (GameObject::m_state->getGlobalY());
	b->outline_opacity = 1.0f;
	graphics::drawRect(trueX, trueY, BlockSize, BlockSize, *b);


}

void Block::update(float dt) {

}

Block::~Block() {

}

