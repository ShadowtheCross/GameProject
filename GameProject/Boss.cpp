#include "Entities.h"

Boss::Boss(GameState* gs) : Enemy(gs, "Boss") {
}

void Boss::init(int spawn_x, int spawn_y) {
	Enemy::init(1, 3, 
		"Assets\\Textures\\Enemies\\NightBorn\\", "Assets\\Textures\\Enemies\\NightBorn\\Animations.txt",
		1.0, 1.0, 1.0, 1.0,
		spawn_x, spawn_y,
		1500);
	
	mobilize->direction_x = Movement::Direction::Left;
	spawnHealthTrigger1 = max_health * 2.0 / 3.0;
	spawnHealthTrigger2 = max_health / 3.0;
}

void Boss::draw() {
	animation->draw();
	mobilize->draw();
}

void Boss::update(float dt) {
	float elapse;
	float Time = graphics::getDeltaTime();
	if (!spawned1 && spawnHealthTrigger1 > health) {
		Skeleton* s;
		Goblin* g;
		
		s = new Skeleton(GameObject::m_state);
		s->init(-3, 98);
		g = new Goblin(GameObject::m_state);
		g->init(-3, 98);
		GameObject::m_state->appendEntity(s);
		GameObject::m_state->appendEntity(g);
		
		s = new Skeleton(GameObject::m_state);
		s->init(8, 98);
		g = new Goblin(GameObject::m_state);
		g->init(8, 98);
		GameObject::m_state->appendEntity(s);
		GameObject::m_state->appendEntity(g);
		spawned1 = true;
	}
	if (!spawned2 && spawnHealthTrigger2 > health) {
		Skeleton* s;
		Goblin* g;
		s = new Skeleton(GameObject::m_state);
		s->init(-3, 98);
		g = new Goblin(GameObject::m_state);
		g->init(-3, 98);
		GameObject::m_state->appendEntity(s);
		GameObject::m_state->appendEntity(g);

		s = new Skeleton(GameObject::m_state);
		s->init(8, 98);
		g = new Goblin(GameObject::m_state);
		g->init(8, 98);
		GameObject::m_state->appendEntity(s);
		GameObject::m_state->appendEntity(g);
		
		spawned2 = true;
	}






	if (abs(playerDistanceX()) < 4.0f) {
		aggrivate = true;
		
	}
	//Idle Behaviour
	if (mobilize->direction_x == Movement::Direction::Right) {
		animation->setCurrent("IdleRight");
	}
	else {
		animation->setCurrent("IdleLeft");
	}

	if (deathTimer.isRunning()) {
		elapse = deathTimer;
		if (mobilize->direction_x == Movement::Direction::Right) {
			animation->setCurrent("DeathRight");
		}
		else {
			animation->setCurrent("DeathLeft");
		}
		if (!deathTimer.isRunning()) {
			kill();
		}
		mobilize->gravity(Time);
		mobilize->update(dt);
		animation->update(dt);
		return;

	}


	if(attackTimer.isRunning()) {
		elapse = attackTimer;
		if (mobilize->direction_x == Movement::Direction::Right) {
			animation->setCurrent("AttackRight");
		}
		else {
			animation->setCurrent("AttackLeft");
		}
		if (!attackTimer.isRunning()) attack(50.0,20);
		mobilize->gravity(Time);
		mobilize->update(dt);
		animation->update(dt);
		return;
	}
	elapse = attackCooldown;



	float dx_p = playerDistanceX();
	float dy_p = playerDistanceY();

	if (aggrivate) {
		if (abs(dx_p) >= .3f) {
			if (dx_p > 0) {
				mobilize->direction_x = Movement::Direction::Right;
				animation->setCurrent("RunRight");
			}
			else {
				mobilize->direction_x =Movement::Direction::Left;
				animation->setCurrent("RunLeft");
			}
			mobilize->moveX(Time, mobilize->direction_x,1.0);
		}  
		if (abs(dx_p) < 0.5f && !attackCooldown.isRunning()) {
			attackTimer.start();
			attackCooldown.start();
			animation->fromTheStart("AttackRight");
			animation->fromTheStart("AttackLeft");
		}

	}
	mobilize->gravity(Time);
	mobilize->update(dt);
	animation->update(dt);

}

void Boss::damage(float damage) {
	health -= damage;
	if (health < 0 && !deathTimer.isRunning()) {
		deathTimer.start();
		GameObject::m_state->playerWon();
		graphics::stopMusic();
	}

}


void Boss::attack(float dmg,float ripperEffect) {
	float dx_p = playerDistanceX();
	float dy_p = playerDistanceY();
	if (dx_p * mobilize->direction_x < 1 && dx_p * mobilize->direction_x > 0 && abs(dy_p) < 0.5f) {
		GameObject::m_state->damagePlayer(dmg);
		GameObject::m_state->increaseHealth(-ripperEffect);
	}
}

Boss::~Boss() {

}