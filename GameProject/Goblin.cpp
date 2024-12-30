#include "Enemies.h"

Goblin::Goblin(GameState* gs) : Enemy(gs, "Goblin") {

}

void Goblin::init(int spawn_x, int spawn_y) {
	Enemy::init(1, 1, 1, 12,
		"Assets\\Textures\\Enemies\\Goblin\\", "Assets\\Textures\\Enemies\\Goblin\\Animations.txt",
		2.0 / 4.0, 2.0 / 4.0,
		spawn_x, spawn_y);
}
void Goblin::update(float dt) {
	float Time = graphics::getDeltaTime();
	if (mobilize->direction_x == Movement::Direction::Right) {
		animation->setCurrent("IdleRight");
	}
	else {
		animation->setCurrent("IdleLeft");
	}

	mobilize->gravity(Time);
	animation->update(dt);
	mobilize->update(dt);
}

void Goblin::draw() {
	animation->draw();
	mobilize->draw();
}

Goblin::~Goblin() {}