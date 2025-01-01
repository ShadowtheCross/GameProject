#include "Character.h"

Goblin::Goblin(GameState* gs) : Character(gs, "Goblin") {

}

void Goblin::init(int spawn_x, int spawn_y) {
	Character::init(0.2, 0.5, 1, 12,
		"Assets\\Textures\\Enemies\\Goblin\\", 
		"Assets\\Textures\\Enemies\\Goblin\\Animations.txt",
		2.0 / 4.0, 2.0 / 4.0, 
		spawn_x, spawn_y,
		50);
	attackTimer = new Timer(.5f,Timer::TIMER_ONCE);
	attackCooldown = new Timer(2.0f, Timer::TIMER_ONCE);
	dashTimer = new Timer(0.4f, Timer::TIMER_ONCE);
	dashCooldown = new Timer(2.0f, Timer::TIMER_ONCE);
	
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
	float dP = playerDistance();

	elapse = *attackCooldown;
	elapse = *dashCooldown;

	
		
			
	if (dashTimer->isRunning()) {
		if (mobilize->ability_x == Movement::Direction::Right) {
			animation->setCurrent("RunRight");
		}
		else {
			animation->setCurrent("RunLeft");
		}
		mobilize->dash(Time,mobilize->ability_x);
		elapse = *dashTimer;
	} else 
	if (attackTimer->isRunning()) {
		if (mobilize->ability_x == Movement::Direction::Right) {
			animation->setCurrent("AttackRight");
		}
		else {
			animation->setCurrent("AttackLeft");
		}		
		elapse = *attackTimer;
	}
	else {

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
		if (abs(dP) < 1.f) {
		
			if (!dashCooldown->isRunning()) {
				dashTimer->start();
				dashCooldown->start();
				mobilize->ability_x = dP > 0 ? Movement::Direction::Right : Movement::Direction::Left;;
			}	
		}
		 if (abs(dP) <  0.2f) {
			if (!attackCooldown->isRunning()) {
				attackCooldown->start();
				attackTimer->start();
				mobilize->ability_x = dP>0 ? Movement::Direction::Right : Movement::Direction::Left;
			} 
		}
		
		if (dP < -0.2) {
			mobilize->moveX(Time, Movement::Direction::Left);
			mobilize->direction_x = Movement::Direction::Left;
			animation->setCurrent("RunLeft");
		}
		else if(dP >0.2) {
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
	delete attackTimer, attackCooldown,dashTimer,dashCooldown;
}