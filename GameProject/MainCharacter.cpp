#include "MainCharacter.h"
#include "AnimationHandler.h"

float counter = 0;
MainCharacter::MainCharacter(GameState* gs, std::string name) : GameObject(gs, name) {
	animation = new AnimationHandler(gs, name);
	mobilize = new Movement(gs, name);
	dashTimer = new Timer(0.30f, Timer::TIMER_ONCE);
	jumpTimer = new Timer(.5f, Timer::TIMER_ONCE);
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


}

void MainCharacter::update(float dt) {
	float Time = graphics::getDeltaTime() / 10.f;
	
	//Stability movement
	mobilize->moveY(Time, Movement::Direction::Up, 0.1f);

	
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
		mobilize->moveY(Time, Movement::Direction::Up,1);
		if (mobilize->onCeiling()) jumpTimer->stop();
	}


	if (mobilize->onFloor()) {
		if (graphics::getKeyState(graphics::SCANCODE_LEFT)) {
			mobilize->direction_x = Movement::Direction::Left;
			mobilize->moveX(Time,Movement::Direction::Left);
			animation->setCurrent("RunLeft");
		}
		if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) {
			mobilize->direction_x = Movement::Direction::Right;
			mobilize->moveX(Time, mobilize->direction_x);
			animation->setCurrent("RunRight");
		}
		if (graphics::getKeyState(graphics::SCANCODE_SPACE) && !jumpTimer->isRunning()) {
			jumpTimer->start();
			std::cout << "ERROR if pressed more than once";
		}else if (graphics::getKeyState(graphics::SCANCODE_LSHIFT)) {
			dashTimer->start();
		}
	}
	else {
		if (graphics::getKeyState(graphics::SCANCODE_LEFT)) {
			mobilize->direction_x = Movement::Direction::Left;
			mobilize->moveX(Time, mobilize->direction_x);
			if (mobilize->rising()) {
				animation->setCurrent("RiseRight");
			}
			else {
				animation->setCurrent("FallRight");
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) {
			mobilize->direction_x = Movement::Direction::Right;
			mobilize->moveX(Time, mobilize->direction_x);
			if (mobilize->rising()) {
				animation->setCurrent("RiseLeft");
			}
			else {
				animation->setCurrent("FallLeft");
			}
		}
	}
	
	mobilize->moveY(Time, Movement::Direction::Up, 0.1f);


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