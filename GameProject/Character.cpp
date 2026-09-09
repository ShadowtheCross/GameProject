#include "Entities.h"

Character::Character(GameState* gs, std::string name) : Entity(gs, name) {
	animation = new AnimationHandler(gs, name + " Animation");
	mobilize = new Movement(gs, name + "Physics");
}

void Character::init(float acc_x, float acc_y, 
	std::string TexturesDirectory, std::string LoadScript,
	float width, float height,float animation_width,float animation_height,
	int spawn_x, int spawn_y,
	 float m_h) {
	Entity::init(spawn_x, spawn_y);
	this->width = width;
	this->height = height;
	
	animation->init(TexturesDirectory, LoadScript,
		animation_width, animation_height,
		&(Entity::true_x), &(Entity::true_y));
	mobilize->init(acc_x, acc_y,
		width, height,
		&(Entity::true_x), &(Entity::true_y));
	health = m_h;
	max_health = m_h;


}
void Character::kill() {
	GameObject::setActive(false);
}

int Character::getDirectionX() {
	return mobilize->direction_x;
}


void Character::update(float dt) {
	
}

void Character::draw() {
	mobilize->draw();
	animation->draw();
}

Character::~Character() {
	delete mobilize;
	delete animation;

}