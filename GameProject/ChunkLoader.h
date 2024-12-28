#pragma once
#include "GameLogic.h"
#include "unordered_map"
#include "GameState.h"
#include <vector>
#include "Config.h"
#include <list>

class ChunkLoader : public GameObject{
	// The size to render the objects and entities
	
	int chunkSize = 100;


	std::unordered_map<int,std::unordered_map<int, std::list<GameObject*> >> activeRenderer;
	ChunkLoader(GameState * gs, std::string name);

	void init(int chunkSize);
	void appendAt(float x, float y, GameObject* object);
	void draw();
	void update(float dt);


	ChunkLoader();



};