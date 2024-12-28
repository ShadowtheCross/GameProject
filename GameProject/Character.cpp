#include "Character.h"

Character::Character(GameState* gs, std::string name) :  AnimationHandler(gs, name + "Animation"), Movement(gs, name + "Physics") {

}

void Character::init(float acc_x, float acc_y,
	float max_x, float max_y,
	std::string TexturesDirectory, std::string LoadScript,
	float width, float height,
	int spawn_x, int spawn_y) {
	true_x = spawn_x;
	true_y = spawn_y;
	AnimationHandler::init(TexturesDirectory, LoadScript, width, height, &true_x, &true_y);
	Movement::init(acc_x, acc_y, max_x, max_y, width, height, &true_x, &true_y);
}

void Character::update(float dt) {
	AnimationHandler::setCurrent("IdleRight");

	moveUp();
	moveDown();
	gravity();


	Movement::update(dt);
	AnimationHandler::update(dt);
}
void Character::draw() {
	Movement::draw();
	AnimationHandler::draw();
}

Character::~Character() {

}

