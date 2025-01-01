#include "Character.h"

Entity::Entity(GameState* gs,std::string name) : GameObject(gs, "Entity") {

}

void Entity::init() {

}

void Entity::update(float dt) {

}

void Entity::draw() {

}
Entity::~Entity() {

}


float Entity::getX() {
	return true_x;
}
float Entity::getY() {
	return true_y;
}