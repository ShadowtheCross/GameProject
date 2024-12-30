#include "Character.h"

Goblin::Goblin(GameState* gs) : Character(gs, "Goblin") {

}

void Goblin::init(int spawn_x, int spawn_y) {
	Character::init(0.1, 1, 0.3, 12,
		"Assets\\Textures\\Enemies\\Goblin\\", "Assets\\Textures\\Enemies\\Goblin\\Animations.txt",
		2.0 / 4.0, 2.0 / 4.0,
		spawn_x, spawn_y);
	attackTimer = new Timer(0.3,Timer::TIMER_ONCE);
	movementCooldown = new Timer(1.0f, Timer::TIMER_ONCE);
	dashTimer = new Timer(0.3, Timer::TIMER_ONCE);
}
void Goblin::update(float dt) {
	float Time = graphics::getDeltaTime();
	




	if (Character::mobilize->direction_x == Movement::Direction::Right) {
		Character::animation->setCurrent("IdleRight");
	}
	else {
		Character::animation->setCurrent("IdleLeft");
	}

	float elapse;
	if (movementCooldown->isRunning()) {
		elapse = *movementCooldown;
		if (dashTimer->isRunning()) {
			elapse = *dashTimer;
			mobilize->dash(Time,mobilize->direction_x);
		}
		else {
			attackTimer->start();
		}
		if (attackTimer->isRunning()) {
			elapse = *attackTimer;
			if (mobilize->direction_x == Movement::Direction::Left) {
				Character::animation->setCurrent("AttackRight");
			}
			else {
				Character::animation->setCurrent("AttackLeft");
			}
		}
		
	}
	else {
float dP = playerDistance();

	if (!aggrivate) {
	
		bool veryClose = abs(dP) < 2;
		bool leftSeen = dP > -5 && mobilize->direction_x == Movement::Direction::Left;
		bool rightSeen = dP < 5 && mobilize->direction_x == Movement::Direction::Right;
		if (abs(dP) <2) {
			aggrivate = true;
		}
		/*else if( leftSeen || rightSeen) {
			aggrivate = true;
		}*/
	}
	else {
		if (abs(dP) < 0.5f) {
			dashTimer->start();
			movementCooldown->start();
		}
		if (dP < 0) {
			mobilize->moveX(Time, Movement::Direction::Left);
			mobilize->direction_x = Movement::Direction::Left;
			animation->setCurrent("RunLeft");
		}
		else {
			mobilize->moveX(Time, Movement::Direction::Right);
			mobilize->direction_x = Movement::Direction::Right;
			animation->setCurrent("RunRight");
		}
	}
	}







	
	



	mobilize->gravity(Time);


	Character::mobilize->gravity(Time);
	Character::animation->update(dt);
	Character::mobilize->update(dt);
}

void Goblin::draw() {
	Character::animation->draw();
	Character::mobilize->draw();
}

Goblin::~Goblin() {
	delete attackTimer, movementCooldown;
}