#include "Entities.h"

Boss::Boss(GameState* gs) : Character(gs, "Boss") {

}

void Boss::init(int spawn_x, int spawn_y) {
	true_x = spawn_x;
	true_y = spawn_y;
	animation->init("Assets\\Textures\\Enemies\\NightBorn\\", "Assets\\Textures\\Enemies\\NightBorn\\Animations.txt",
		1, 1,
		&true_x, &true_y);
	mobilize->init(1, 3, 3, 12,
		1.0/3.0, 1.0 / 3.0,
		&true_x, &true_y);
	health = 300;
	max_health = 300;
	mobilize->direction_x = Movement::Direction::Right;
}

void Boss::draw() {
	animation->draw();
	mobilize->draw();
}

void Boss::update(float dt) {
	if (abs(playerDistanceX()) < 4.0f) {
		aggrivate = true;
	}

	//Idle Behaviour
	if (mobilize->direction_x == Movement::Direction::Right) {
		animation->setCurrent("RightIdle");
	}
	else {
		animation->setCurrent("LeftIdle");
	}



}

Boss::~Boss() {
	delete animation, mobilize;
}