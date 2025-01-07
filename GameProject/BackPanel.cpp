#include "Back.h"


VisualBackground::VisualBackground(GameState *gs)  : GameObject(gs,"BackPanel") {}

void VisualBackground::init(float screenPercentageWidth, float screenPercentageHeight,std::string BackGroundPath) {
	width = screenPercentageWidth * Config::window_width;
	height - screenPercentageHeight * Config::window_height;
	backBrush.texture = BackGroundPath;
	backBrush.outline_opacity = 0.0f;
}
float counter3 = 0;
void VisualBackground::draw() {
	//First center_x and center_y to render
	for (float x = c_x; x < c_x + Config::window_width * 3; x += Config::window_width) {
		for (float y = c_y; y < c_y + Config::window_width * 3; y += Config::window_width) {
				graphics::drawRect(x, y, width, height, backBrush);


		}
	}


}

void VisualBackground::update(float dt) {
	c_x =  GameObject::m_state->getGlobalX()/2;
	c_y = GameObject::m_state->getGlobalY() /2;
	if (counter3 > 1000) {
		counter3 = 0.0f;
		std::cout << c_x << " : " << c_y << std::endl;
	}
	counter3 = graphics::getGlobalTime() / 100;

}



VisualBackground::~VisualBackground() {

}

