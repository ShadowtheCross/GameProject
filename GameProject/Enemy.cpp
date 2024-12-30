#include "Enemies.h"

Enemy::Enemy(GameState* gs, std::string name) : GameObject(gs, name) {
	animation = new AnimationHandler(gs, name + " Animation");
	mobilize = new Movement(gs, name + "Physics");
}

void Enemy::init(float acc_x, float acc_y, float max_x, float max_y,
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
void Enemy::kill() {
	GameObject::setActive(false);
}

void Enemy::update(float dt) {}

void Enemy::draw() {
	mobilize->draw();
	animation->draw();
}

Enemy::~Enemy() {
	delete mobilize;
	delete animation;

}