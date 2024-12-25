#pragma once
#include "GameLogic.h"
#include "GameState.h"
#include <iostream>

class EventHandler : GameObject {
public:
	/*
	* Every special event we want to describe will be specified here
	* 
	* 
	* 
	* 
	*/

	bool moveRight = false,
		moveLeft = false,
		jump = false;




	EventHandler(GameObject* gs, std::string name); 

	void init();
	void update();
	void draw();

	~EventHandler();
	
};