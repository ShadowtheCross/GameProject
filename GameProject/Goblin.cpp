#include "Entities.h"

Goblin::Goblin(GameState* gs) : Character(gs, "Goblin") {
	attackTimer1 = new Timer(.5f,Timer::TIMER_ONCE);
	attackCooldown = new Timer(2.0f, Timer::TIMER_ONCE);
	dashTimer = new Timer(0.4f, Timer::TIMER_ONCE);
	dashCooldown = new Timer(2.0f, Timer::TIMER_ONCE);
	stunt = new Timer(0.5f, Timer::TIMER_ONCE);
	death = new Timer(0.5f, Timer::TIMER_ONCE);
}

void Goblin::init(int spawn_x, int spawn_y) {
	Character::init(1.2, 0.5, 2, 12,
		"Assets\\Textures\\Enemies\\Goblin\\", 
		"Assets\\Textures\\Enemies\\Goblin\\Animations.txt",
		2.0 / 4.0, 2.0 / 4.0, 
		spawn_x, spawn_y,
		50);
	

}




void Goblin::update(float dt) {
	float Time = graphics::getDeltaTime()/10;
	float elapse;
	
	float dx_p = Character::playerDistanceX();
	float dy_p = playerDistanceY();
	if (mobilize->direction_x == Movement::Direction::Right) {
		animation->setCurrent("IdleRight");
	}
	else {
		animation->setCurrent("IdleLeft");
	}
	elapse = *attackCooldown;
	elapse = *dashCooldown;


	if (death->isRunning()) {
		if (Character::mobilize->direction_x == Movement::Direction::Right) {
			Character::animation->setCurrent("DeathRight");
		}
		else {
			Character::animation->setCurrent("DeathLeft");
		}
		Character::mobilize->gravity(Time);
		Character::animation->update(dt);
		Character::mobilize->update(dt);
		elapse = *death;
		if (!death->isRunning()) kill();
		return;
	}
	if (stunt->isRunning()) {
		if (Character::mobilize->direction_x == Movement::Direction::Right) {
			Character::animation->setCurrent("TakeHitRight");
		}
		else {
			Character::animation->setCurrent("TakeHitLeft");
		}
		Character::mobilize->gravity(Time);
		Character::animation->update(dt);
		Character::mobilize->update(dt);
		elapse = *stunt;
		return;
	}
	if (attackTimer1->isRunning()) {
		if (mobilize->direction_x == Movement::Direction::Right) {
			animation->setCurrent("AttackRight");
		}
		else {
			animation->setCurrent("AttackLeft");
		}
		elapse = *attackTimer1;
		if (!attackTimer1->isRunning()) {
			attack();
		}
		Character::mobilize->gravity(Time);
		Character::animation->update(dt);
		Character::mobilize->update(dt);
		return;
	}
	if (dashTimer->isRunning()) {
		if (mobilize->direction_x == Movement::Direction::Right) {
			animation->setCurrent("RunRight");
		}
		else {
			animation->setCurrent("RunLeft");
		}
		elapse = *dashTimer;
		mobilize->dash(Time, mobilize->direction_x);
		Character::mobilize->gravity(Time);
		Character::animation->update(dt);
		Character::mobilize->update(dt);
		return;
	}



	









	if (aggrivate) {
		if (dx_p > 0) {
			mobilize->moveX(Time, Movement::Direction::Right);
			animation->setCurrent("RunRight");
			mobilize->direction_x = Movement::Direction::Right;
		}
		 if (dx_p < 0 ) {			
			mobilize->moveX(Time, Movement::Direction::Left);
			animation->setCurrent("RunLeft");
			mobilize->direction_x = Movement::Direction::Left;
		}
		if (!dashCooldown->isRunning() && abs(dx_p) < 1) {
			dashTimer->start();
			dashCooldown->start();
		}
		else if (abs(dx_p) < 0.3 && !attackCooldown->isRunning() && abs(dy_p) < 0.3f) {
			attackTimer1->start();
			attackCooldown->start();
		} 		
	}






	if ((aggrivate && abs(dx_p) < 8 ) || (!aggrivate && abs(dx_p) <2) ) {
		aggrivate = true;
	}
	else {
		aggrivate = false;
	}



	


	Character::mobilize->gravity(Time);
	Character::animation->update(dt);
	Character::mobilize->update(dt);
}

void Goblin::attack() {
	float dx_p = playerDistanceX();
	float dy_p = playerDistanceY();
	if (dx_p *mobilize->direction_x  < 0.5f && dx_p * mobilize->direction_x > 0 && abs(dy_p) < 0.3f) {
		GameObject::m_state->damagePlayer(10);
	}
}

void Goblin::damage(float dmg) {
	health -= dmg;
	if (health <= 0) {
		death->start();
		graphics::playSound("Assets\\SoundTrack\\Enemies\\Goblin\\Death.mp3", 0.1);
	}
	dashCooldown->stop();
	dashTimer->stop();
	attackCooldown->stop();
	attackTimer1->stop();
	stunt->start();
}




void Goblin::draw() {
	Character::animation->draw();
	Character::mobilize->draw();
}

Goblin::~Goblin() {
	delete attackTimer1, attackCooldown,dashTimer,dashCooldown;
}