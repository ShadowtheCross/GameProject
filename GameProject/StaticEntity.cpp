#include "Entities.h" 

StaticEntity::StaticEntity(GameState* gs, std::string name) : Entity(gs,name) {
	animations = new AnimationHandler(gs, name + " Animations ");
}

void StaticEntity::init(float x, float y, std::string TextureFolder) {
	Entity::init(x, -y);
	animations->init(TextureFolder, TextureFolder + "Animations.txt", 1, 1, &(Entity::true_x), &(Entity::true_y) );

}

void StaticEntity::update(float dt) {
	animations->update(dt);
}

void StaticEntity::draw() {
	animations->draw();
}


StaticEntity::~StaticEntity() {
	delete animations;
}
