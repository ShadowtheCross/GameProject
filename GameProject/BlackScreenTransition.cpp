#include "BlackScreen.h"

BlackScreen::BlackScreen(GameState* gs) : GameObject(gs, "BlackScreen") {}

void BlackScreen::init() {
	screen.outline_opacity = 1.0f;
	screen.fill_color[0] = 0.0f;
	screen.fill_color[1] = 0.0f;
	screen.fill_color[2] = 0.0f;
}

void BlackScreen::draw() {
	graphics::drawRect(Config::window_width / 2, Config::window_height / 2, Config::window_width, Config::window_height, screen);
}

void BlackScreen::update(float dt) {
	screen.fill_opacity += rate *graphics::getDeltaTime() /1000.f;
	
	if (screen.fill_opacity < 0) {
		screen.fill_opacity = 0.0f;
		rate = 0.0f;
		return;
	}
	if (screen.fill_opacity > 1) {
		screen.fill_opacity = 1.0f;
		rate = 0.0f;
		return;
	}
}

void BlackScreen::activate() {
	rate = 1;
}
void BlackScreen::deactivate() {
	rate = -1;
}

bool BlackScreen::isActivated() {
	return screen.fill_opacity == 1.0f;
}
bool BlackScreen::isDeactivated() {
	return screen.fill_opacity == 0.0f;
}


BlackScreen::~BlackScreen() {

}