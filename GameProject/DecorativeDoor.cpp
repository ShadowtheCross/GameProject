#include "Entities.h"


DecorativeDoor::DecorativeDoor(GameState* gs, std::string name) : StaticEntity(gs, name) {
	animations = new AnimationHandler(gs, name + " Animation");
}


void DecorativeDoor::init(float x, float y) {
	StaticEntity::init(x ,  y , "Assets\\Textures\\Objects\\Door\\");
}

void DecorativeDoor::update(float dt) {

}

void DecorativeDoor::draw() {
	StaticEntity::draw();
}

DecorativeDoor::~DecorativeDoor() {

}