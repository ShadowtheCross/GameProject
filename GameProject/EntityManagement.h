#pragma once
#include <unordered_map>
#include "GameLogic.h"
#include "GameState.h"
#include "Config.h"
#include "Entities.h"
#include <list>
#include <vector>
class StaticEntity;

class EntityHandler : public GameObject {
//	std::unordered_map<int, std::unordered_map<int, std::list<class Entity*>>> Entities;
	std::list<class Character*> Entities;
	std::vector<StaticEntity* > StaticEntities;
	class MainCharacter* player;
public:

	EntityHandler(GameState* gs);

	void init();
	void update(float dt);
	void draw();

	void attack(float dmg);

	void teleportPlayer(float x, float y);

	void appendStaticEntity(StaticEntity * en);
	void clearStaticEntities();

	void damageEnemies(float dmg);
	void damagePlayer(float dmg);
	void playerDamageEnemies(float dmg);

	void clearHandler();

	void regeneratePlayerHealth(float Health);
	void increasePlayerHealth(float Health);
	
	bool enemiesInRange(float x, float range);




	void appendEntity(Character* en);
	void wipeEntities();
	~EntityHandler();




};