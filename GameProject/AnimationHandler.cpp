#include "GameState.h"
#include "GameLogic.h"
#include <iostream>
#include <stack>
#include <fstream>
#include "AnimationHandler.h"
#include "Miscallenious.h"

AnimationHandler::AnimationHandler(GameState * sg, std::string name) : GameObject(sg, name) {

}

void AnimationHandler::init(std::string TexturesDirectory, std::string LoadScript,
	float width,float height ,
	float* x_offset, float * y_offset) {
	Loader.open(LoadScript);
	std::string lineInfo,folder, animationFrames, frameDurations;
	

	std::getline(Loader, lineInfo);
	tripleDotSplit(lineInfo, folder, animationFrames, frameDurations);


	Animations[folder] = new SingleAnimation(GameObject::m_state, folder);
	Animations[folder]->init(TexturesDirectory+folder + "\\", std::stoi(animationFrames), std::stof(frameDurations), width, height, x_offset, y_offset);
	
	cur = folder;
	deleter.push(folder);
	
	while (Loader.good()) {
		std::getline(Loader,lineInfo);
		tripleDotSplit(lineInfo, folder, animationFrames, frameDurations);
	
		Animations[folder] = new SingleAnimation(GameObject::m_state, folder);
		Animations[folder]->init(TexturesDirectory + folder +"\\", std::stoi(animationFrames), std::stof(frameDurations), width, height, x_offset, y_offset);
	}
	
	Loader.close();
}

void AnimationHandler::update(float dt) {
	Animations[cur]->update(dt);
}

void AnimationHandler::draw() {
	Animations[cur]->draw();
	
}

void AnimationHandler::fromTheStart(std::string anim) {
	Animations[anim]->startFromTheBegining();
}


void AnimationHandler::setCurrent(std::string anim) {
	cur = anim;
}

AnimationHandler::~AnimationHandler() {
	while (!deleter.empty()) {
		delete Animations[deleter.top()];
		deleter.pop();
	}
}