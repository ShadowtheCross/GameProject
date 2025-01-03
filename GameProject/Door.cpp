#include "Entities.h"


Door::Door(GameState* gs, std::string name) : StaticEntity(gs, name) {
	animations = new AnimationHandler(gs, name + " Animation");

}


void Door::init(float x, float y) {
	true_x = x;
	true_y = y;
	this->static_offset_x = static_offset_x;
	this->static_offset_y = static_offset_y;
	animations->init("Assets\\Textures\\Objects\\Door\\", "Assets\\Textures\\Objects\\Door\\Animations.txt",
		1.0, 1.0,
		&true_x, &true_y);

}

void Door::update(float dt) {
	bool InteractPressed = graphics::getKeyState(graphics::SCANCODE_E);
	animations->setCurrent("Opened");
	if (abs(playerDistanceX() )< 4 && abs(playerDistanceY() ) <4  && InteractPressed) {
		animations->setCurrent("Closed");
	}
	animations->update(dt);
}

void Door::draw() {
	animations->draw();
}

Door::~Door() {
	delete animations;
}