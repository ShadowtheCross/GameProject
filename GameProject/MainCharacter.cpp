#include "MainCharacter.h"
#include "AnimationHandler.h"

float counter = 0;
MainCharacter::MainCharacter(GameState* gs, std::string name) : GameObject(gs, name) {
	animation = new AnimationHandler(gs, name);
	mobilize = new Movement(gs, name);
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
	mobilize->moveUp();
	if (!graphics::getKeyState(graphics::SCANCODE_LEFT) && !graphics::getKeyState(graphics::SCANCODE_RIGHT)) {
		animation->setCurrent("Idle");
	}
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) {
		mobilize->moveRight();
		animation->setCurrent("RunRight");
	}
	if (graphics::getKeyState(graphics::SCANCODE_LEFT)) {
		mobilize->moveLeft();
		animation->setCurrent("RunLeft");
	}
	mobilize->moveDown();
	mobilize->gravity();

	animation->update(dt);
	mobilize->update(dt);
}

void MainCharacter::draw() {
	animation->draw();
	mobilize->draw();

}

MainCharacter::~MainCharacter() {
	delete animation, mobilize;
}