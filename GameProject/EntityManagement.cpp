#include "EntityManagement.h"

EntityHandler::EntityHandler(GameState* gs) : GameObject(gs,"EntityHandler" ) {
	player = new MainCharacter(gs, "Character");
}
void EntityHandler::init() {
	player->init(0,0);
}

void EntityHandler::update(float dt) {
	std::list<Entity*>::iterator it;
	it = Entities.begin();
	while (it != Entities.end() ) {
		(*it)->update(dt);
		if (!(*it)->isActive() ) {
			delete* it;
			it = Entities.erase(it++);
		}
		else {
			it++;
		}
	}
	for (int i = 0; i < StaticEntities.size(); i++) {

		StaticEntities[i]->update(dt);
	}

	player->update(dt);

}

void EntityHandler::draw() {
	std::list<Entity*>::iterator it;
	for (it = Entities.begin(); it != Entities.end(); ++it) {
		(*it)->draw();
	}
	for (int i = 0; i < StaticEntities.size(); i++) {
		StaticEntities[i]->draw();
	}
	player->draw();

}

void EntityHandler::appendStaticEntity(StaticEntity* en) {
	
	StaticEntities.push_back(en);
}

void EntityHandler::clearStaticEntities() {
	for (int i = 0; i < StaticEntities.size(); i++) {
		delete StaticEntities[i];

	}
	StaticEntities.clear();
}



void EntityHandler::damagePlayer(float dmg) {
	player->damage(dmg);
}

void EntityHandler::damageEnemies(float dmg) {
	std::list<Entity*>::iterator it;
	float dx;
	float dy;
	for (it = Entities.begin(); it != Entities.end(); ++it) {
		dx =  (*it)->getX() - player->getX();
		dy =  (*it)->getY() - player->getY();
		if (  ( dx*player->getDirectionX() <1 &&  0 <dx * player->getDirectionX())  && abs(dy)< 0.2f) {
			(*it)->damage(dmg);
		}
		
	}
}

void EntityHandler::teleportPlayer(float x, float y) {
	player->teleport(x, y);

}


void EntityHandler::wipeEntities() {
	std::list<Entity*>::iterator it;
	for (it = Entities.begin(); it != Entities.end(); it++) {
		delete (*it);
	}
	Entities.clear();
}


EntityHandler::~EntityHandler() {
	wipeEntities();
	Entities.clear();
	clearStaticEntities();
	delete player;
}

void EntityHandler::appendEntity(Entity* en) {
		Entities.push_back(en);
}