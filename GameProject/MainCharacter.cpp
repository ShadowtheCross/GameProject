#include "Entities.h"

float counter = 0;
MainCharacter::MainCharacter(GameState* gs, std::string name) : Character(gs, name) {
	dashTimer = new Timer(0.15f, Timer::TIMER_ONCE);
	dashCooldown = new Timer(0.3f, Timer::TIMER_ONCE);
	jumpTimer1 = new Timer(0.05, Timer::TIMER_ONCE);
	jumpCoolDown = new Timer(.2f, Timer::TIMER_ONCE);
	attackTimer1 = new Timer(0.45, Timer::TIMER_ONCE);
	attackTimer2 = new Timer(0.45, Timer::TIMER_ONCE);
	nextAttackWindow = new Timer(0.3f, Timer::TIMER_ONCE);
	stuntTimer = new Timer(0.5f, Timer::TIMER_ONCE);
}

void MainCharacter::init(int spawn_x, int spawn_y) {
	
	mobilize->init(1, 3, 3, 12, 0.3, .5f, &true_x, &true_y);
	animation->init("Assets\\Textures\\MC\\", "Assets\\Textures\\MC\\Animations.txt",
		2.5, 1.25,
		&true_x, &true_y);
	health = 100;
	max_health = 100;

	GameObject::m_state->setPlayerX(&true_x);
	GameObject::m_state->setPlayerY(&true_y);


}




void MainCharacter::update(float dt) {
	float Time = graphics::getDeltaTime() / 10.f;
	canHit = true;
	counter += Time;
	if (counter > 100) {
		counter = 0;
		std::cout << "Health " << health << std::endl;
	}

	float cooldown;

	if (stuntTimer->isRunning()) {
		cooldown = *stuntTimer;
		if (mobilize->direction_x == Movement::Direction::Right) {
			animation->setCurrent("TakeHitRight");
		}
		else {
			animation->setCurrent("TakeHitLeft");
		}

		mobilize->gravity(Time);
		animation->update(dt);
		mobilize->update(dt);
		return;
	}



	//Idle unless changed
	if (mobilize->direction_x == Movement::Direction::Right) {
		animation->setCurrent("IdleRight");
	}
	else {
		animation->setCurrent("IdleLeft");

	}


	graphics::MouseState st;
	graphics::getMouseState(st);
	bool attacking = st.button_left_pressed;

	cooldown = *dashCooldown;
	cooldown = *jumpCoolDown;
	bool activeAbility = false;

	//Ability set
	if (dashTimer->isRunning()) {
		float elapsed1= *dashTimer;
		mobilize->dash(Time,mobilize->direction_x);
		activeAbility = true;
		canDash = false;
		canHit = false;
		return;
	}
	if (jumpTimer1->isRunning()) {
		float elapsed2 = *jumpTimer1;
		mobilize->moveY(Time, Movement::Direction::Up,6);
		activeAbility = true;
		if (mobilize->onCeiling()) jumpTimer1->stop();
	}
	float elapsed3;
	elapsed3 = *nextAttackWindow;
	if (attackTimer1->isRunning()) {
		elapsed3 = *attackTimer1;
		if (mobilize->direction_x == Movement::Direction::Right) {
			animation->setCurrent("Attack1Right");
		}
		else {
			animation->setCurrent("Attack1Left");
		}
		if (!attackTimer1->isRunning()) {
			attack(Config::attackDamage1);
			nextAttackWindow->start();
		}
		mobilize->gravity(Time);
		animation->update(dt);
		mobilize->update(dt);
		return;
	}
	else if (attackTimer2->isRunning()) {
		nextAttackWindow->stop();
		elapsed3 = *attackTimer2;
		if (mobilize->direction_x == Movement::Direction::Right) {
			animation->setCurrent("Attack2Right");
		}
		else {
			animation->setCurrent("Attack2Left");
		}
		if (!attackTimer2->isRunning()) {
			attack(Config::attackDamage2);
		}
		mobilize->gravity(Time);

		animation->update(dt);
		mobilize->update(dt);
		return;
	}

	


	
	bool left = graphics::getKeyState(graphics::SCANCODE_A);
	bool right = graphics::getKeyState(graphics::SCANCODE_D);
	bool jump = graphics::getKeyState(graphics::SCANCODE_SPACE);
	bool dash = graphics::getKeyState(graphics::SCANCODE_LSHIFT);
	
	bool idle = (left && right) || (!left && !right) || activeAbility;

	// Movement Configurer
	
	if (left) {
		mobilize->direction_x = Movement::Direction::Left;	
		mobilize->moveX(Time, Movement::Direction::Left);
	}
	else if(right){
		mobilize->direction_x = Movement::Direction::Right;
		mobilize->moveX(Time, Movement::Direction::Right);
	}
	


	//Animations and ability triggers


	
	if (mobilize->onFloor()) {
		canDash = true;
		canJumpAgain = true;

		if (left) {
			animation->setCurrent("RunLeft");
		}
		else if(right) {
			animation->setCurrent("RunRight");
		}
		if (jump && !jumpCoolDown->isRunning()) {
			jumpTimer1->start();
			jumpCoolDown->start();
		}  
		
		if (attacking) {
			if (nextAttackWindow->isRunning()) {
				attackTimer2->start();
				if (mobilize->direction_x == Movement::Direction::Right) {
					animation->fromTheStart("Attack2Right");
				}
				else {
					animation->fromTheStart("Attack2Left");
				}
			} else if (!attackTimer1->isRunning()) {
				attackTimer1->start();
				if (mobilize->direction_x == Movement::Direction::Right) {
					animation->fromTheStart("Attack1Right");
				}
				else {
					animation->fromTheStart("Attack1Left");
				}
			}
			
		} 
	}
	else {
		if (canJumpAgain && jump && !jumpCoolDown->isRunning()) {
			jumpTimer1->start();
			canJumpAgain = false;
		}
		if (mobilize->rising()) {
			if (mobilize->direction_x == Movement::Direction::Right) {
				animation->setCurrent("RiseRight");
			}
			else {
				animation->setCurrent("RiseLeft");
			}
		}
		else {
			if (mobilize->direction_x == Movement::Direction::Right) {
				animation->setCurrent("FallRight");
			}
			else {
				animation->setCurrent("FallLeft");
			}
		}


	}
	if (dash && !dashCooldown->isRunning() && !idle && canDash) {
		dashTimer->start();
		dashCooldown->start();
	}


	mobilize->gravity(Time);

	animation->update(dt);
	mobilize->update(dt);
}

void MainCharacter::draw() {
	animation->draw();
	mobilize->draw();

}
void MainCharacter::attack(float dmg) {
	GameObject::m_state->damageEnemies(dmg);
}

void MainCharacter::damage(float dmg) {
	if (!canHit) {
		return;
	}
	health -= dmg;
	if (health <= 0) {
		kill();
	}
	stuntTimer->start();
	attackTimer1->stop();
	attackTimer2->stop();
	dashTimer->stop();
}

void MainCharacter::teleport(float x, float y) {
	true_x = x;
	true_y = y;

}


MainCharacter::~MainCharacter() {
	delete animation, mobilize;
	delete jumpTimer1, dashTimer;
}