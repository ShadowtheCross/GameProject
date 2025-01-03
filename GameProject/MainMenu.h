#pragma once
#include "GameState.h"
#include <iostream> 
#include "GameLogic.h"
#include "timer.h"
#include "Config.h"
class MainPlayerMenu : public GameObject {
protected:
	graphics::Brush BackGround;
	graphics::Brush Plain, Red;
	int counter = 0;
	int centerx=0, centery=0;
	int uppery=0, lowery = 0;
	bool controlViewer = false;
	Timer play = Timer(.2f, Timer::TIMER_ONCE);

public:
	MainPlayerMenu(class GameState *gs ): GameObject(gs,"MainMenu") {}
	void init();
	void update(float dt);
	void draw();
	void startGame();
	~MainPlayerMenu();
};
