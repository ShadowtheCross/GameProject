#include "Character.h"

float counter = 0;
MainCharacter::MainCharacter(GameState* gs, std::string name) : Character(gs, name) {
	dashTimer = new Timer(0.30f, Timer::TIMER_ONCE);
	dashCooldown = new Timer(0.6f, Timer::TIMER_ONCE);
	jumpTimer = new Timer(0.05, Timer::TIMER_ONCE);
	jumpCoolDown = new Timer(.3f, Timer::TIMER_ONCE);
}

void MainCharacter::init(float acc_x, float acc_y,
	float max_x, float max_y,
	std::string TexturesDirectory, std::string LoadScript,
	float width, float height,
	int spawn_x, int spawn_y) {
	true_x = spawn_x;
	true_y = spawn_y;
	animation->init(TexturesDirectory, LoadScript,
		width, height,
		&true_x, &true_y);
	mobilize->init(acc_x, acc_y,
		max_x, max_y,
		width, height,
		&true_x, &true_y);

	GameObject::m_state->setPlayerX(&true_x);
	GameObject::m_state->setPlayerY(&true_y);


}

void MainCharacter::update(float dt) {
	float Time = graphics::getDeltaTime() / 10.f;
	
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