#include "Entities.h"

Chest::Chest(GameState *gs,std::string name) : StaticEntity(gs,name) {
	animations = new AnimationHandler(gs, "");
}

void Chest::init(float x, float y) {
	StaticEntity::init(x, y, "Assets\\Textures\\Objects\\Chest\\");
}

void Chest::draw() {
	StaticEntity::draw();
}

void Chest::update(float dt) {
	if (opened == true) {
		animations->setCurrent("Opened");
		return;
	}
	bool InteractPressed = graphics::getKeyState(graphics::SCANCODE_E);
	animations->setCurrent("Closed");
	if (abs(playerDistanceX()) < 1 && abs(playerDistanceY()) < 2 && InteractPressed) {
		opened = true;
		GameObject::m_state->increaseHealth(50);
	}
	StaticEntity::update(dt);
}

Chest::~Chest() {
}