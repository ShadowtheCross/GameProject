#include "Entities.h"

Entity::Entity(GameState* gs,std::string name) : GameObject(gs, "Entity") {

}

void Entity::init() {

}
float Entity::playerDistanceX() {
	return GameObject::m_state->getPlayerX() - true_x;
}
float Entity::playerDistanceY() {
	return GameObject::m_state->getPlayerY() - true_y;
}


void Entity::update(float dt) {

}

void Entity::draw() {

}
Entity::~Entity() {

}

void Entity::attack() {
	
}
void Entity::damage(float dmg) {
}


float Entity::getX() {
	return true_x;
}
float Entity::getY() {
	return true_y;
}