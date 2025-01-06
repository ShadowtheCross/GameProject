#include "Entities.h"


Door::Door(GameState* gs, std::string name) : StaticEntity(gs, name) {
	animations = new AnimationHandler(gs, name + " Animation");
}


void Door::init(float x, float y) {
	true_x = x;
	true_y = -y;
	animations->init("Assets\\Textures\\Objects\\Door\\", "Assets\\Textures\\Objects\\Door\\Animations.txt",
		1.0, 1.0,
		&true_x, &true_y);

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
	animations->update(dt);
}

void Door::draw() {
	animations->draw();
}

Door::~Door() {
	delete animations;
}