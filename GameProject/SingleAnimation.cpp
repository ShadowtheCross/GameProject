#include "SingleAnimation.h"
#include "GameLogic.h"
#include "GameState.h"
#include <iostream>
#include <string>

SingleAnimation::SingleAnimation(GameState* gs, std::string name) : GameObject(gs, name) {

}

void SingleAnimation::init(std::string getAnimationFolder, int framesNumber, float durationFrame, float w, float h, float* x_offset, float* y_offset) {
	Frames = new graphics::Brush[framesNumber];
	Frames[0].outline_opacity = 0.0f;
	for (int i = 0; i < framesNumber; i++) {
		Frames[i].texture = getAnimationFolder + std::to_string(i)+ ".png";
		Frames[i].outline_opacity = 0.0f;
	}
	width = w * GameObject::m_state->getBlockSize();
	height = h * GameObject::m_state->getBlockSize();

	numOfFrames = framesNumber;
	frameDuration = durationFrame;
	loc_x = x_offset;
	loc_y = y_offset;
}

void SingleAnimation::update(float dt) {
	//check if elapsed time has passed to move to the next frame

	if (measure < frameDuration) {
		measure += graphics::getDeltaTime();
	}
	else {
		counter++;
		measure = .0f;
	}
	if (counter == numOfFrames) {
		counter = 0;
	}
}

void SingleAnimation::draw() {
	int BlockSize = GameObject::m_state->getBlockSize();
	int trueX = GameObject::m_state->getGlobalX()+ (*loc_x) * BlockSize;
	int trueY = GameObject::m_state->getGlobalY() + (*loc_y) * BlockSize;
	graphics::drawRect( trueX, trueY,width, height ,Frames[counter]);
}

SingleAnimation::~SingleAnimation() {
	delete[]Frames;
}

