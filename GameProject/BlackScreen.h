#pragma once
#include "sgg/graphics.h"
#include "GameLogic.h"
#include "GameState.h"

class BlackScreen :public GameObject {
	graphics::Brush screen;
	float rate=0;
public:
	BlackScreen(GameState* gs);
	
	void init();
	void draw();
	void update(float dt);
	void activate();
	bool isActivated();
	bool isDeactivated();
	void deactivate();



	~BlackScreen();


};