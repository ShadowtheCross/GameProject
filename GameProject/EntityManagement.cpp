#include "EntityManagement.h"

EntityHandler::EntityHandler(GameState* gs) : GameObject(gs,"EntityHandler" ) {
}
void EntityHandler::init() {
	player = new MainCharacter(GameObject::m_state, "Character");
	player->init(0,0);
}

void EntityHandler::update(float dt) {
	std::list<Character*>::iterator it;
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
	std::list<Character*>::iterator it;
	for (int i = 0; i < StaticEntities.size(); i++) {
		StaticEntities[i]->draw();
	}	
	for (it = Entities.begin(); it != Entities.end(); ++it) {
		(*it)->draw();
	}
	
	player->draw();

}

void EntityHandler::regeneratePlayerHealth(float Health) {
	player->regenerateHealth(Health);
}

void EntityHandler::increasePlayerHealth(float Health) {
	player->increaseHealth(Health);
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
	std::list<Character*>::iterator it;
	float dx;
	float dy;
	for (it = Entities.begin(); it != Entities.end(); ++it) {
		dx =  (*it)->playerDistanceX();
		dy =  (*it)->playerDistanceY();
		if (  ( abs(dx*player->getDirectionX() ) < 1 &&  0 > dx * player->getDirectionX())  && abs(dy)< 0.4f) {
			(*it)->damage(dmg);
		}
		
	}
}

void EntityHandler::teleportPlayer(float x, float y) {
	player->teleport(x, y);

}


void EntityHandler::wipeEntities() {
	std::list<Character*>::iterator it;
	for (it = Entities.begin(); it != Entities.end(); it++) {
		delete (*it);
	}
	Entities.clear();
}


EntityHandler::~EntityHandler() {
	wipeEntities();
	Entities.clear();
	clearStaticEntities();
	StaticEntities.clear();
	delete player;
}

void EntityHandler::appendEntity(Character* en) {
		Entities.push_front(en);
}

void EntityHandler::clearHandler() {
	wipeEntities();
	clearStaticEntities();
	
}

bool EntityHandler::enemiesInRange(float x, float range) {
	std::list<Character*>::iterator it;
	int BlockSize = GameObject::m_state->getBlockSize();
	float dx;
	float dy;
	for (it = Entities.begin(); it != Entities.end(); ++it) {
		dx = ( (*it)->getX() - x);
		if (abs(dx) < range) return true;
	}
	return false;
}