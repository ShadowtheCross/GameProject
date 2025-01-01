#include "Character.h"

float counter = 0;
MainCharacter::MainCharacter(GameState* gs, std::string name) : Character(gs, name) {
	dashTimer = new Timer(0.15f, Timer::TIMER_ONCE);
	dashCooldown = new Timer(0.3f, Timer::TIMER_ONCE);
	jumpTimer = new Timer(0.05, Timer::TIMER_ONCE);
	jumpCoolDown = new Timer(.3f, Timer::TIMER_ONCE);
}

void MainCharacter::init(int spawn_x, int spawn_y) {
	
	Character::init(1, 1, 1, 12,
		"Assets\\Textures\\MC\\", "Assets\\Textures\\MC\\Animations.txt",
		2.0 / 3.0, 2.0 / 3.0, 
		spawn_x, spawn_y,
		100);

	GameObject::m_state->setPlayerX(&true_x);
	GameObject::m_state->setPlayerY(&true_y);


}

void MainCharacter::update(float dt) {
	float Time = graphics::getDeltaTime() / 10.f;
	std::cout << true_x << " " << Character::true_y << std::endl;
	

	//Stability movement

	
	if (mobilize->direction_x == Movement::Direction::Right) {
		animation->setCurrent("IdleRight");
	}
	else {
		animation->setCurrent("IdleLeft");
	}


	if (dashTimer->isRunning()) {
		float elapsed1= *dashTimer;
		mobilize->dash(Time,mobilize->direction_x);
	}
	if (jumpTimer->isRunning()) {
		float elapsed2 = *jumpTimer;
		mobilize->moveY(Time, Movement::Direction::Up,5);
		if (mobilize->onCeiling()) jumpTimer->stop();
	}
	float cooldown = *dashCooldown;
	cooldown = *jumpCoolDown;


	
	bool left = false, right = false, jump = false, dash =false,hit = false;
	left = graphics::getKeyState(graphics::SCANCODE_A);
	right = graphics::getKeyState(graphics::SCANCODE_D);
	jump = graphics::getKeyState(graphics::SCANCODE_SPACE);
	dash = graphics::getKeyState(graphics::SCANCODE_LSHIFT);
	graphics::MouseState st;
	graphics::getMouseState(st);
	hit = st.button_left_pressed;
	bool doNothing = false;
	bool idle = (left && right) || (!left && !right);

	// Movement Configurer
	if (  idle  ) {
		//Set movement to idle
		doNothing = true;
	}
	else {
		if (left) {
			mobilize->direction_x = Movement::Direction::Left;	
			mobilize->moveX(Time, Movement::Direction::Left);

		}
		else if(right){
			mobilize->direction_x = Movement::Direction::Right;
			mobilize->moveX(Time, Movement::Direction::Right);

		}
	}


	//Invoke direction



	if (mobilize->onFloor()) {
		if (doNothing) {
			if (mobilize->direction_x == Movement::Direction::Right) {
				animation->setCurrent("IdleRight");
			}
			else {
				animation->setCurrent("IdleLeft");
			}
		}
		else if (left) {
			animation->setCurrent("RunLeft");
		}
		else {
			animation->setCurrent("RunRight");
		}
		if (jump && !jumpCoolDown->isRunning()) {
			jumpTimer->start();
			jumpCoolDown->start();
		}
		if (dash && !dashCooldown->isRunning() && !idle) {
			dashTimer->start();
			dashCooldown->start();
		}
	}
	else {
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
	
	mobilize->gravity(Time);

	animation->update(dt);
	mobilize->update(dt);
}

void MainCharacter::draw() {
	animation->draw();
	mobilize->draw();

}

MainCharacter::~MainCharacter() {
	delete animation, mobilize;
	delete jumpTimer, dashTimer;
}