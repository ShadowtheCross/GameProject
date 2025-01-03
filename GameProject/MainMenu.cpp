#include "MainMenu.h"
#include "GameState.h"



void MainPlayerMenu::init() {
	BackGround.texture = "Assets\\Textures\\MainMenu\\MainMenuScreen.png";
	BackGround.outline_opacity = 0.0f;
	graphics::setWindowBackground(BackGround);
	Red.fill_color[1] = .0f; Red.fill_color[2] = .0f;
	centerx = Config::window_width/2;
	centery = Config::window_height/2;
	uppery = centery - (float) Config::window_height/6.0;
	lowery = centery + (float) Config::window_height / 6.0;
	graphics::setFont("Assets\\Fonts\\ImperialScript-Regular.ttf");
}

void MainPlayerMenu::update(float dt) {
	bool up = graphics::getKeyState(graphics::SCANCODE_UP);
	bool down = graphics::getKeyState(graphics::SCANCODE_DOWN);
	//Run cooldown to move up and down
	if (play.isRunning()) {
		float elapse = play;
	}
	if (!play.isRunning()) {
		if (up) {
			counter--;
			play.start();
		}
		if (down) {
			counter++;	
			play.start();
		}
		if (counter > 2) {
			counter = 0;
		}
		else if (counter < 0) {
			counter = 2;
		}
	}
	
	bool Enter = graphics::getKeyState(graphics::SCANCODE_RETURN);
	bool Q = graphics::getKeyState(graphics::SCANCODE_Q);
	if (Enter) {
		if (counter == 0) {
			GameObject::m_state->nextLevel();
		}
		if (counter == 1) {
			controlViewer = true;
		}
		if (counter == 1 && controlViewer && Q) {
			controlViewer = false;
		}

		if (counter == 2|| Q) {	

			graphics::stopMessageLoop();
		}

	}
}

void MainPlayerMenu::draw() {
	graphics::drawRect(centerx, centery, Config::window_width, Config::window_height, BackGround);

	switch (counter)
	{
	case 0:
		graphics::drawText(centerx, uppery, 100, "Start", Red);
		graphics::drawText(centerx, centery, 100, "Controls", Plain);
		graphics::drawText(centerx, lowery, 100, "Quit", Plain);
		break;
	case 1:
		graphics::drawText(centerx, uppery, 100, "Start", Plain);
		graphics::drawText(centerx, centery, 100, "Controls", Red);
		graphics::drawText(centerx, lowery, 100, "Quit", Plain);
		break;
	case 2:
		graphics::drawText(centerx, uppery, 100, "Start", Plain);
		graphics::drawText(centerx, centery, 100, "Controls", Plain);
		graphics::drawText(centerx, lowery, 100, "Quit", Red);
		break;
	default:
		break;
	}

}

MainPlayerMenu::~MainPlayerMenu() {

}