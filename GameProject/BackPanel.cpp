#include "Back.h"


VisualBackground::VisualBackground(GameState *gs,std::string name)  : GameObject(gs,name) {}

void VisualBackground::init(float screenPercentageWidth, float screenPercentageHeight,std::string BackGroundPath) {
	width = screenPercentageWidth * Config::mainPlayerWidth;
	height - screenPercentageHeight * Config::mainPlayerHeight;
	backBrush.texture = BackGroundPath;
	backBrush.outline_opacity = 0.0f;
}

void VisualBackground::draw() {
	float c_x = Config::window_width/2 ;
	float  c_y = -Config::window_height/2;
	std::cout << c_x << " : " << c_y << "\n";
	for (int i = -3; i < 3; i++) {
		for (int b = -3; b < 3; b++) {
			graphics::drawRect(c_x*i ,c_y*b, 200*width, 200*height, backBrush);

		}
	}


}

void VisualBackground::update(float dt) {

}



VisualBackground::~VisualBackground() {

}

