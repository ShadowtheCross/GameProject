#include "Back.h"


VisualBackground::VisualBackground(GameState *gs)  : GameObject(gs,"BackPanel") {}

void VisualBackground::init(float screenPercentageWidth, float screenPercentageHeight,std::string BackGroundPath) {
	width = screenPercentageWidth * Config::window_width;
	height =  screenPercentageHeight * Config::window_height;
	backBrush.texture = BackGroundPath;
	backBrush.outline_opacity = 0.0f;
}
float counter3 = 0;
void VisualBackground::draw() {
	//First center_x and center_y to render
	for (float x = c_x- 2*width; x < c_x + width *3; x += width) {
		for (float y = c_y -2*height;  y < c_y + height * 3; y += height) {
				graphics::drawRect(x, y, width, height, backBrush);


		}
	}


}

void VisualBackground::update(float dt) {
	int BlockSize = GameObject::m_state->getBlockSize();
	c_x = GameObject::m_state->getGlobalX() - ( (int)  (GameObject::m_state->getGlobalX() / width ) * width) - width/2;
	c_y = GameObject::m_state->getGlobalY() + ( (int)  (GameObject::m_state->getGlobalY() / height) * width) - height/ 4;
	
	if (counter3 > 1000) {
		counter3 = 0.0f;
		std::cout << c_x << " : " << c_y << std::endl;
	}
	counter3 = graphics::getGlobalTime() / 100;

}



VisualBackground::~VisualBackground() {

}

