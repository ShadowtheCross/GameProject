#pragma once
#include "sgg/graphics.h"
#include "GameLogic.h"
#include "GameState.h"
#include "Config.h"

class VisualBackground : public GameObject {
protected:
	float width=0, height=0;
	graphics::Brush backBrush;
public:
	VisualBackground(GameState* gs, std::string name);

	void init(float screenPercentageWidth, float screenPercentageHeight, std::string BackGroundPath);
	void draw();
	void update(float dt);

	~VisualBackground();
};