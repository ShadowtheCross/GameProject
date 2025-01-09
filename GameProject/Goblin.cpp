#include "Entities.h"

Goblin::Goblin(GameState* gs) : Enemy(gs, "Goblin") {
	
}

void Goblin::init(int spawn_x, int spawn_y) {
	Enemy::init(1.2, 0.5, 2, 12,
		"Assets\\Textures\\Enemies\\Goblin\\", 	"Assets\\Textures\\Enemies\\Goblin\\Animations.txt",
		0.5f, 0.5f ,0.5f ,0.5f ,
		spawn_x, spawn_y,
		50);
}




void Goblin::update(float dt) {
	float Time = graphics::getDeltaTime()/10;
	float elapse;
	
	float dx_p = playerDistanceX();
	float dy_p = playerDistanceY();
	if (mobilize->direction_x == Movement::Direction::Right) {
		animation->setCurrent("IdleRight");
	}
	else {
		animation->setCurrent("IdleLeft");
	}
	elapse = attackCooldown;
	elapse = dashCooldown;


	if (death.isRunning()) {
		if (Character::mobilize->direction_x == Movement::Direction::Right) {
			animation->setCurrent("DeathRight");
		}
		else {
			animation->setCurrent("DeathLeft");
		}
		mobilize->gravity(Time);
		animation->update(dt);
		mobilize->update(dt);
		elapse = death;
		if (!death.isRunning()) kill();
		return;
	}
	if (stunt.isRunning()) {
		if (Character::mobilize->direction_x == Movement::Direction::Right) {
			Character::animation->setCurrent("TakeHitRight");
		}
		else {
			Character::animation->setCurrent("TakeHitLeft");
		}
		Character::mobilize->gravity(Time);
		Character::animation->update(dt);
		Character::mobilize->update(dt);
		elapse = stunt;
		return;
	}
	if (attackTimer1.isRunning()) {
		if (mobilize->direction_x == Movement::Direction::Right) {
			animation->setCurrent("AttackRight");
		}
		else {
			animation->setCurrent("AttackLeft");
		}
		elapse = attackTimer1;
		if (!attackTimer1.isRunning()) {
			attack();
		}
		Character::mobilize->gravity(Time);
		Character::animation->update(dt);
		Character::mobilize->update(dt);
		return;
	}
	if (dashTimer.isRunning()) {
		if (mobilize->direction_x == Movement::Direction::Right) {
			animation->setCurrent("RunRight");
		}
		else {
			animation->setCurrent("RunLeft");
		}
		elapse = dashTimer;
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
		if (!dashCooldown.isRunning() && abs(dx_p) < 1) {
			dashTimer.start();
			dashCooldown.start();
		}
		else if (abs(dx_p) < 0.3 && !attackCooldown.isRunning() && abs(dy_p) < 0.3f) {
			attackTimer1.start();
			attackCooldown.start();
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
		death.start();
		graphics::playSound("Assets\\SoundTrack\\Enemies\\Goblin\\Death.mp3", 0.1);
	}
	dashCooldown.stop();
	dashTimer.stop();
	attackCooldown.stop();
	attackTimer1.stop();
	stunt.start();
}




void Goblin::draw() {
	Character::animation->draw();
	Character::mobilize->draw();
}

Goblin::~Goblin() {
	
}