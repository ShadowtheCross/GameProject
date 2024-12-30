#pragma once
#include "AnimationHandler.h"
#include "Movement.h"

class Enemy :public GameObject{
protected:
	class AnimationHandler* animation;
	class Movement* mobilize;
	float true_x = 0.0f, true_y = 0.0f;
public:

	Enemy(GameState* gs, std::string name);

	void init(float acc_x, float acc_y, float max_x, float max_y,
		std::string TexturesDirectory, std::string LoadScript,
		float width, float height,
		int spawn_x, int spawn_y);
	
	void update(float dt);

	float getX() {
		return true_x;
	}
	float getY() {
		return true_y;
	}

	void kill();

	void draw();

	~Enemy();

};

class Goblin :	public Enemy	{
public:
	Goblin(GameState* gs);

	void init(int spawn_x,int spawn_y);
	
	static Goblin* declareAndInit(GameState *gs,int spawn_x, int spawn_y) {
		Goblin* temp = new Goblin(gs);
		temp->init(spawn_x, spawn_y);
		return temp;
	}

	void draw();
	void update(float dt);

	~Goblin();



};


class Skeleton : public Enemy {
public:
	Skeleton(GameState* gs);

	void init(int spawn_x, int spawn_y);

	static Skeleton* declareAndInit(GameState* gs, int spawn_x, int spawn_y) {
		Skeleton* temp = new Skeleton(gs);
		temp->init(spawn_x, spawn_y);
		return temp;
	}

	void draw();
	void update(float dt);

	~Skeleton();



};