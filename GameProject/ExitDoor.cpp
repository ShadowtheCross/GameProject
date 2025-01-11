#include "Entities.h"

ExitDoor::ExitDoor(GameState* gs) : DecorativeDoor(gs, "Door") {
	
}

void ExitDoor::init(float x, float y) {
	DecorativeDoor::init(x, y);
}

void ExitDoor::draw() {
	DecorativeDoor::draw();
}

void ExitDoor::update(float dt) {
	bool InteractPressed = graphics::getKeyState(graphics::SCANCODE_E);
	animations->setCurrent("Closed");
	if (abs(playerDistanceX()) < 1 && abs(playerDistanceY()) < 1 && InteractPressed) {
		if (GameObject::m_state->enemiesInRange(Entity::getX(), 10)) {
			graphics::drawText(Config::window_width/2, Config::window_height/2 -100, 50, "Enemies Nearby", Plain);
		}
		else {
			opened = true;
			NextLevelGo.start();
		}


		
	}
	if (NextLevelGo.isRunning()) {
		float elapse = NextLevelGo;
		if (!NextLevelGo.isRunning()) {
			GameObject::m_state->nextLevel();
		}
	}
	if (opened) animations->setCurrent("Opened");
	DecorativeDoor::update(dt);
}

ExitDoor::~ExitDoor() {

}