#include "Entities.h"

Skeleton::Skeleton(GameState* gs) : Enemy(gs, "Skeleton") {
	
}

void Skeleton::init(int spawn_x, int spawn_y) {
	
	Enemy::init(0.2, 1, 0.5, 12,
		"Assets\\Textures\\Enemies\\Skeleton\\", "Assets\\Textures\\Enemies\\Skeleton\\Animations.txt",
		1.0 / 3.0, 2.0 / 3.0, 6.0 / 4.0, 3.0 / 4.0,
		spawn_x,spawn_y,
		100);
	rate = (float) randomInt(900, 1100)/1000.0f;

}
void Skeleton::update(float dt) {
	float Time = graphics::getDeltaTime();
	float elapse;


	if (death.isRunning()) {
		if (Character::mobilize->direction_x == Movement::Direction::Right) {
			Character::animation->setCurrent("DeathRight");
		}
		else {
			Character::animation->setCurrent("DeathLeft");
		}
		Character::mobilize->gravity(Time);
		Character::animation->update(dt);
		Character::mobilize->update(dt);
		elapse = death;
		if (!death.isRunning()) kill();
		return;
	}
	if (stuntTimer.isRunning()) {
		if (Character::mobilize->direction_x == Movement::Direction::Right) {
			Character::animation->setCurrent("HitRight");
		}
		else {
			Character::animation->setCurrent("HitLeft");
		}
		Character::mobilize->gravity(Time);
		Character::animation->update(dt);
		Character::mobilize->update(dt);
		elapse = stuntTimer;
		return;
	}

	if (attackTimer.isRunning()) {
		if (Character::mobilize->direction_x == Movement::Direction::Right) {
			Character::animation->setCurrent("AttackRight");
		}
		else {
			Character::animation->setCurrent("AttackLeft");
		}
		Character::mobilize->gravity(Time);
		Character::animation->update(dt);
		Character::mobilize->update(dt);
		elapse = attackTimer;
		if (!attackTimer.isRunning()) attack();

		return;
	}
	if (blockTimer.isRunning()) {
		if (Character::mobilize->direction_x == Movement::Direction::Right) {
			Character::animation->setCurrent("BlockRight");
		}
		else {
			Character::animation->setCurrent("BlockLeft");
		}
		Character::mobilize->gravity(Time);
		Character::animation->update(dt);
		Character::mobilize->update(dt);
		elapse = blockTimer;
		
		return;
	}

	if (turnAroundTimer.isRunning()) {
		elapse = turnAroundTimer;
		if (!turnAroundTimer.isRunning()) {
			Character::mobilize->direction_x = playerDistanceX() > 0 ? Movement::Direction::Right : Movement::Direction::Left;
		}
		
	}




	if (Character::mobilize->direction_x == Movement::Direction::Right) {
		Character::animation->setCurrent("IdleRight");
	}
	else {
		Character::animation->setCurrent("IdleLeft");
	}

	float dx_p = playerDistanceX();
	float dy_p = playerDistanceY();

	if (  ( abs(dx_p) < 8 && aggrivate) || abs(dx_p ) < 2 ) {
		aggrivate = true;
	}
	else {
		aggrivate = false;
	}


	if (aggrivate || Enemy::alwaysAgro) {
		
		if (dx_p < -0.2 && mobilize->direction_x == Movement::Direction::Left) {
			mobilize->moveX(Time, Movement::Direction::Left,rate);
			animation->setCurrent("RunLeft");
		}
		else if (dx_p > 0.2 == mobilize->direction_x == Movement::Direction::Right) {
			mobilize->moveX(Time, Movement::Direction::Right,rate);
			animation->setCurrent("RunRight");
		}
		else if(!turnAroundTimer.isRunning()) { turnAroundTimer.start(); }

		if (dx_p < 0.4 && dx_p > -0.4 && abs(dy_p) <0.5f ) {
			if (!attackTimer.isRunning()) {
				attackTimer.start();
				mobilize->direction_x = mobilize->direction_x == Movement::Direction::Right ?  Movement::Direction::Right : Movement::Direction::Left;
			}
		}

	}




	Character::mobilize->gravity(Time);
	Character::animation->update(dt);
	Character::mobilize->update(dt);
}

void Skeleton::attack() {
	float dx_p = playerDistanceX();
	float dy_p = playerDistanceY();
	if (dx_p * mobilize->direction_x < 0.5f && dx_p * mobilize->direction_x > 0 && abs(dy_p) < 0.5f) {
		GameObject::m_state->damagePlayer(20);
	}


}

void Skeleton::damage(float dmg) {
	attackTimer.stop();
	if (sign(playerDistanceX() * mobilize->direction_x) == 1 && !death.isRunning()) {
		blockTimer.start();
		return;
	}
	health -= dmg;
	if (health <= 0) {
		death.start();
		return;
	}
	stuntTimer.start();


}


void Skeleton::draw() {
	Character::animation->draw();
	Character::mobilize->draw();
}

Skeleton::~Skeleton() {}