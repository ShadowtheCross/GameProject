#include "Back.h"


VisualBackground::VisualBackground(GameState *gs)  : GameObject(gs,"BackPanel") {}

void VisualBackground::init(float screenPercentageWidth, float screenPercentageHeight,std::string BackGroundPath) {
	lock_x = screenPercentageWidth * Config::window_width;
	lock_y =  screenPercentageHeight * Config::window_height;
	backBrush.texture = BackGroundPath;
	backBrush.outline_opacity = .0f;
}
float counter3 = 0;
void VisualBackground::draw() {
	//First center_x and center_y to render

	for (float x_draw = start_x - 2*lock_x; x_draw <  start_x + 3 * lock_x; x_draw += lock_x) {
		for (float y_draw = start_y - 2*lock_y; y_draw < start_y + 3 * lock_y; y_draw += lock_y) {
			graphics::drawRect(x_draw, y_draw, lock_x, lock_y, backBrush);
		}
	}



}

void VisualBackground::update(float dt) {
	int BlockSize = GameObject::m_state->getBlockSize();
	float c_x = GameObject::m_state->getGlobalX();
	float c_y = GameObject::m_state->getGlobalY();
	start_x = fmod(c_x, lock_x);
	start_y = fmod(c_y, lock_y);

	if (counter3 > 1000) {
		counter3 = 0.0f;
	}
	counter3 = graphics::getGlobalTime() / 100;

}



VisualBackground::~VisualBackground() {

}

