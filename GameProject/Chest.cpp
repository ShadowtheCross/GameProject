#include "Entities.h"

Chest::Chest(GameState *gs,std::string name) : StaticEntity(gs,name) {
	animations = new AnimationHandler(gs, "");
}

void Chest::init(float x, float y) {
	true_x = x;
	true_y = -y;
	animations->init("Assets\\Textures\\Objects\\Chest\\",
		"Assets\\Textures\\Objects\\Chest\\Animations.txt", 1, 1, &true_x, &true_y);
}

void Chest::draw() {
	animations->draw();
}

void Chest::update(float dt) {
	if (opened == true) {
		animations->setCurrent("Opened");
		return;
	}
	bool InteractPressed = graphics::getKeyState(graphics::SCANCODE_E);
	animations->setCurrent("Closed");
	if (abs(playerDistanceX() - true_x) < 1 && abs(playerDistanceY() - true_y) < 2 && InteractPressed) {
		opened = true;
		GameObject::m_state->increaseHealth(50);
	}
}

Chest::~Chest() {
	delete animations;
}