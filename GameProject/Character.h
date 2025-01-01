#pragma once
#include "AnimationHandler.h"
#include "Movement.h"
#include "timer.h"
#include "Miscallenious.h"


class Entity : public GameObject {

	float true_x = 0, true_y = 0;
public:
	Entity(GameState* gs, std::string name);

	void init();
	void update(float dt);
	void draw();

	virtual float getX();
	virtual float getY();

	~Entity();
};


class Character :public Entity{
protected:
	class AnimationHandler* animation;
	class Movement* mobilize;
	float true_x = 0.0f, true_y = 0.0f;
	float health = 1,max_health =100;
	int width=0, height=0;
public:

	Character(GameState* gs, std::string name);

	void init(float acc_x, float acc_y, float max_x, float max_y,
		std::string TexturesDirectory, std::string LoadScript,
		float width, float height,
		int spawn_x, int spawn_y,
		float m_h);
	
	void update(float dt);

	float getX() {
		return true_x;
	}
	float getY() {
		return true_y;
	}
	float playerDistance();
	void kill();

	void draw();

	~Character();

};



class Goblin : public Character {
	bool aggrivate =false;
	Timer *attackCooldown, * attackTimer, * dashTimer,*dashCooldown;
public:
	Goblin(GameState* gs);

	void init(int spawn_x, int spawn_y);

	static Goblin* declareAndInit(GameState* gs, int spawn_x, int spawn_y) {
		Goblin* temp = new Goblin(gs);
		temp->init(spawn_x, spawn_y);
		return temp;
	}

	void draw();
	void update(float dt);

	~Goblin();



};


class Skeleton : public Character {
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




class MainCharacter : public Character {
	
	//Ability Timers
	class Timer* dashTimer, * dashCooldown,
		* jumpTimer, * jumpCoolDown;




public:
	MainCharacter(GameState* gs, std::string name);


	void init(int spawn_x, int spawn_y);

	void update(float dt);

	void draw();

	~MainCharacter();


};