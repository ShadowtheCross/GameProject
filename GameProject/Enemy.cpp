#include "Entities.h"

Enemy::Enemy(GameState *gs,std::string name) : Character(gs, name +" Enemy") {}

void Enemy::init(float acc_x, float acc_y, 
	std::string TexturesDirectory, std::string LoadScript,
	float width, float height, float animation_width, float animation_height,
	int spawn_x, int spawn_y,
	float m_h) {
	Character::init(acc_x, acc_y,
		TexturesDirectory, LoadScript,
		width, height, animation_width, animation_height,
		spawn_x,spawn_y,
		m_h);
	rate = ((float)randomInt(900, 1100)) / 1000.0f;
	Enemy::alwaysAgro = GameObject::m_state->getAgro();
}
void Enemy::update(float dt) {}
void Enemy::draw()  {}
Enemy::~Enemy() {}
void Enemy::attack() {}
void Enemy::damage(float dmg) {}
