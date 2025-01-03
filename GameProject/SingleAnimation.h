#pragma once
#include <iostream>
#include "GameLogic.h"
#include "GameState.h"
#include "sgg/graphics.h"

class SingleAnimation : public GameObject {
	graphics::Brush* Frames;
	int numOfFrames;
	float * loc_x, * loc_y;
	float frameDuration;
	int counter, width =0,height=0;
	float measure = .0f;

	/*
	* The program inits with a directory in which the frames are listed from 0-n
	* 	* 
	*/
public:
	
	SingleAnimation(GameState *gs, std::string name);
	void init(std::string getAnimationFolder, int framesNumber, float durationFrame, float w, float h, float* x_offset, float * y_offset);
	void update(float dt);
	void draw();
	void play();

	void startFromTheBegining();

	~SingleAnimation();



};

