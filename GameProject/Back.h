#pragma once
#include "sgg/graphics.h"
#include "GameLogic.h"
#include "GameState.h"
#include "Config.h"
#include <cmath>

class VisualBackground : public GameObject {
protected:
	float lock_x=0, lock_y=0;
	float start_x = 0, start_y = 0;
	graphics::Brush backBrush;
public:
	VisualBackground(GameState* gs);

	void init(float screenPercentageWidth, float screenPercentageHeight, std::string BackGroundPath);
	void draw();
	void update(float dt);

	~VisualBackground();
};