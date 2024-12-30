#include "Enemies.h"

Skeleton::Skeleton(GameState* gs) : Enemy(gs, "Skeleton") {

}

void Skeleton::init(int spawn_x, int spawn_y) {
	Enemy::init(1, 1, 1, 12,
		"Assets\\Textures\\Enemies\\Skeleton\\", "Assets\\Textures\\Enemies\\Skeleton\\Animations.txt",
		3.0 / 4.0, 3.0 / 4.0,
		spawn_x, spawn_y);
}
void Skeleton::update(float dt) {
	float Time = graphics::getDeltaTime();
	if (mobilize->direction_x == Movement::Direction::Right) {
		animation->setCurrent("IdleRight");
	}
	else {
		animation->setCurrent("IdleLeft");
	}
	std::cout << "TESTING";
	mobilize->gravity(Time);
	animation->update(dt);
	mobilize->update(dt);
}

void Skeleton::draw() {
	animation->draw();
	mobilize->draw();
}

Skeleton::~Skeleton() {}