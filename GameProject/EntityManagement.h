#pragma once
#include <unordered_map>
#include "GameLogic.h"
#include "GameState.h"
#include "Config.h"
#include "Character.h"
#include "Character.h"
#include <list>


class EntityHandler : public GameObject {
	std::unordered_map<int, std::unordered_map<int, std::list<class Entity*>>> Entities;
	class MainCharacter* player;
public:

	EntityHandler(GameState* gs);

	void init();
	void update(float dt);
	void draw();

	void appendEntity(Entity* en);
	void wipeEntities();
	~EntityHandler();




};