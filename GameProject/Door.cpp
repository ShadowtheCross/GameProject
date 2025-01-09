#include "Entities.h"


Door::Door(GameState* gs, std::string name) : StaticEntity(gs, name) {
	animations = new AnimationHandler(gs, name + " Animation");
}


void Door::init(float x, float y) {
	StaticEntity::init(x ,  y , "Assets\\Textures\\Objects\\Door\\");
}

void Door::update(float dt) {
	bool InteractPressed = graphics::getKeyState(graphics::SCANCODE_E);
	animations->setCurrent("Closed");
	if (abs(playerDistanceX())< 1 && abs(playerDistanceY()) <1  && InteractPressed) {
		opened = true;
		NextLevelGo.start();
	}
	if (NextLevelGo.isRunning()) {
		float elapse = NextLevelGo;
		if (!NextLevelGo.isRunning()) {
			GameObject::m_state->nextLevel();
		}
	}
	if(opened) animations->setCurrent("Opened");
	StaticEntity::update(dt);
}

void Door::draw() {
	StaticEntity::draw();
}

Door::~Door() {

}