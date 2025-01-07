#pragma once
#include "sgg/graphics.h"
#include "GameLogic.h"
#include "GameState.h"
#include "Config.h"

class VisualBackground : public GameObject {
protected:
	float width=0, height=0;
	float c_x = 0, c_y = 0;
	graphics::Brush backBrush;
public:
	VisualBackground(GameState* gs);

	void init(float screenPercentageWidth, float screenPercentageHeight, std::string BackGroundPath);
	void draw();
	void update(float dt);

	~VisualBackground();
};