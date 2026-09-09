#pragma once
#include "GameState.h"
#include "GameLogic.h"
#include <iostream>
#include <stack>
#include <fstream>
#include "SingleAnimation.h"
#include "unordered_map"



class AnimationHandler : public GameObject{

	std::ifstream Loader;
	std::unordered_map<std::string, class SingleAnimation*> Animations;
	std::stack<std::string> deleter;
	std::string cur;//default animation
	
public:
	AnimationHandler(GameState* sg, std::string name);

	void init(std::string TexturesDirectory, std::string LoadScript, 
		float width, float height, 
		float* x_offset, float* y_offset);
	// Folder - Animation Frames - Duration

	void setCurrent(std::string anim);
	void fromTheStart(std::string anim);
	void update(float dt);

	void draw();

	~AnimationHandler();


};

