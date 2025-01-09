#include "Entities.h"

Spikes::Spikes(GameState* gs) :StaticEntity(gs, "Spike") {
	animations = new AnimationHandler(gs, "Spike Handler");
}

void Spikes::init(float x, float y) {
	StaticEntity::init(x, y, "Assets\\Textures\\Objects\\Spikes\\");
}


void Spikes::update(float dt) {
	float dx_p = playerDistanceX();
	float dy_p = playerDistanceY();
	if (abs(dy_p)< 1 && abs(dx_p) < 1) {
		GameObject::m_state->damagePlayer(10000);
	}
	animations->setCurrent("Spikes");
	StaticEntity::update(dt);
}
void Spikes::draw() {
	StaticEntity::draw();
}

Spikes::~Spikes() {
}