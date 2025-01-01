#include "EntityManagement.h"

EntityHandler::EntityHandler(GameState* gs) : GameObject(gs,"EntityHandler" ) {
	player = new MainCharacter(gs, "Character");
}
void EntityHandler::init() {
	player->init(0,0);
}

void EntityHandler::update(float dt) {
	int BlockSize = GameObject::m_state->getBlockSize();
	int cx = player->getX();
	int cy = player->getY();
	int start_x = cx - ( (float) Config::window_width *0.8/BlockSize);
	int start_y = cy - ((float)Config::window_height * 0.8 / BlockSize);
	int end_x = cx + ((float)Config::window_width * 0.8 / BlockSize);
	int end_y = cy + ((float)Config::window_height * 0.8 / BlockSize);
	std::list<Entity*>::iterator it;
	for (int x = start_x; x < end_x; x++) {
		for (int y = start_y; y < end_y; y++) {
			if (!Entities[x][y].empty()) {
				it = Entities[x][y].begin();
				for (it = Entities[x][y].begin(); it != Entities[x][y].end(); it++) {
					(*it)->update(dt);
				}
			}
		}
	}




	player->update(dt);

}

void EntityHandler::draw() {
	int BlockSize = GameObject::m_state->getBlockSize();
	int cx = player->getX();
	int cy = player->getY();
	int start_x = cx - ((float)Config::window_width * 0.8 / BlockSize);
	int start_y = cy - ((float)Config::window_height * 0.8 / BlockSize);
	int end_x = cx + ((float)Config::window_width * 0.8 / BlockSize);
	int end_y = cy + ((float)Config::window_height * 0.8 / BlockSize);
	std::list<Entity*>::iterator it;
	for (int x = start_x; x < end_x; x++) {
		for (int y = start_y; y < end_y; y++) {
			if (!Entities[x][y].empty()) {
				it = Entities[x][y].begin();
				for (it = Entities[x][y].begin(); it != Entities[x][y].end(); it++) {
					(*it)->draw();
				}
			}
		}
	}
	player->draw();

}

void EntityHandler::wipeEntities() {
	std::list<Entity*>::iterator it;
	for (auto& x : Entities) {
		for (auto& y : x.second) {
			it = y.second.begin();
			for (it = y.second.begin(); it != y.second.end(); it++) {
				delete* it;
			}

		}
	}
	Entities.clear();
}


EntityHandler::~EntityHandler() {
	wipeEntities();
	Entities.clear();
	delete player;
}

void EntityHandler::appendEntity(Entity* en) {
	
	int x = en->getX();
	int y = en->getY();

	Entities[x][y].push_back(en);
}