#include "Entities.h"

Spikes::Spikes(GameState* gs) :StaticEntity(gs, "Spike") {
	animations = new AnimationHandler(gs, "Spike Handler");
}

void Spikes::init(float x, float y) {
	true_x = x;
	true_y = -y;
	animations->init("Assets\\Textures\\Objects\\Spikes\\", "Assets\\Textures\\Objects\\Spikes\\Animations.txt", 1, 1, &true_x, &true_y);
}


void Spikes::update(float dt) {
	float dx_p = playerDistanceX();
	float dy_p = playerDistanceY();
	if (abs(dy_p)< 1 && abs(dx_p) < 1) {
		GameObject::m_state->damagePlayer(10000);
	}
	animations->setCurrent("Spikes");

}
void Spikes::draw() {
	animations->draw();
}

Spikes::~Spikes() {
	delete animations;
}