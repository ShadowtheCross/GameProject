#include "Character.h"

Skeleton::Skeleton(GameState* gs) : Character(gs, "Skeleton") {

}

void Skeleton::init(int spawn_x, int spawn_y) {
	Character::init(0.2, 1, 0.5, 12,
		"Assets\\Textures\\Enemies\\Skeleton\\", "Assets\\Textures\\Enemies\\Skeleton\\Animations.txt",
		6.0 / 4.0, 3.0 / 4.0,
		spawn_x, spawn_y,
		100);
}
void Skeleton::update(float dt) {
	float Time = graphics::getDeltaTime();
	if (Character::mobilize->direction_x == Movement::Direction::Right) {
		Character::animation->setCurrent("IdleRight");
	}
	else {
		Character::animation->setCurrent("IdleLeft");
	}
	Character::mobilize->gravity(Time);
	Character::animation->update(dt);
	Character::mobilize->update(dt);
}

void Skeleton::draw() {
	Character::animation->draw();
	Character::mobilize->draw();
}

Skeleton::~Skeleton() {}