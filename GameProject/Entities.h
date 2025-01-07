#pragma once
#include "AnimationHandler.h"
#include "Movement.h"
#include "timer.h"
#include "Miscallenious.h"


class Entity : public GameObject {
protected:
	float true_x = 0, true_y = 0;
public:
	Entity(GameState* gs, std::string name);

	void init();
	void update(float dt);
	void draw();
	virtual void attack();
	virtual void damage(float dmg);
	virtual float getX();
	virtual float getY();

	float playerDistanceX();
	float playerDistanceY();


	~Entity();
};

/*
* 
* Static Entities are entities meant to be present(drawn) 
*  or to trigger under certain conditions
* 
* WARNING: ALL STATIC ENTITIES ARE TO BE PART OF A SPECIAL BLOCK AND NOT INDEPENDANT
*  TO MAXIMIZE PERFORMANCE AND CONFUSION FROM THE ENTITY HANDLER
*/

class StaticEntity : public Entity {
public:
	StaticEntity(GameState* gs, std::string name) : Entity(gs,name) {}

	void init(float x, float y) {}
	void update(float dt) {}
	void draw() {}
	void attack() {}
	void damage(float dmg) {}
	


	~StaticEntity() {}


};

class Door :public StaticEntity {
	bool opened = false;
    protected:
	AnimationHandler* animations;
        Timer NextLevelGo = Timer(0.5f, Timer::TIMER_ONCE);
    public:

		Door* declareAndInit(GameState* gs, float x, float y) {
			Door* temp = new Door(gs, "Door");
			temp->init(x, y);
			return temp;
		}


		Door(GameState* gs, std::string name);

		void init(float x, float y);
		void update(float dt);
		void draw();

    
	



	~Door();

};


class Chest :public StaticEntity {
	AnimationHandler* animations;
	bool opened = false;
public:

	Chest* declareAndInit(GameState* gs, float x, float y) {
		Chest* temp = new Chest(gs, "Door");
		temp->init(x, y);
		return temp;
	}


	Chest(GameState* gs, std::string name);

	void init(float x, float y);
	void update(float dt);
	void draw();

	~Chest();
};

class Spikes : public StaticEntity {
protected:
	AnimationHandler* animations;
public:
	Spikes(GameState* gs);
	void init(float x, float y);
	void draw();
	void update(float dt);
	~Spikes();


};



/*
* 
* Definition of the Character Class along with allthe active Entities in Game
* 
* 
*/
class Character :public Entity{
protected:
	class AnimationHandler* animation;
	class Movement* mobilize;
	float true_x = 0.0f, true_y = 0.0f;
	float health = 1,max_health =100;
	int width=0, height=0;
	bool canDash = false;
	bool canHit = true;
public:
	int getDirectionX();
	Character(GameState* gs, std::string name);

	void init(float acc_x, float acc_y, float max_x, float max_y,
		std::string TexturesDirectory, std::string LoadScript,
		float width, float height,
		int spawn_x, int spawn_y,
		float m_h);
	
	float playerDistanceX();
	float playerDistanceY();

	
	void update(float dt);

	float getX() {
		return true_x;
	}
	float getY() {
		return true_y;
	}
	


	void attack() {}

	void damage(float dmg) {}
	


	void kill();

	void draw();

	~Character();

};



class Goblin : public Character {
	bool aggrivate =false;
	Timer *attackCooldown, * attackTimer1, * dashTimer,*dashCooldown,*stunt,*death;
public:
	Goblin(GameState* gs);

	void init(int spawn_x, int spawn_y);


	static Goblin* declareAndInit(GameState* gs, int spawn_x, int spawn_y) {
		Goblin* temp = new Goblin(gs);
		temp->init(spawn_x, spawn_y);
		return temp;
	}

	void attack();

	void damage(float dmg);



	void draw();
	void update(float dt);

	~Goblin();



};


class Skeleton : public Character {
public:
	
	
	Skeleton(GameState* gs);
	bool aggrivate = false;
	Timer* death,*turnAroundTimer,*attackTimer,*blockTimer,*stuntTimer;
	void init(int spawn_x, int spawn_y);

	static Skeleton* declareAndInit(GameState* gs, int spawn_x, int spawn_y) {
		Skeleton* temp = new Skeleton(gs);
		temp->init(spawn_x, spawn_y);
		return temp;
	}

	void attack();

	void damage(float dmg);


	void draw();
	void update(float dt);

	~Skeleton();



};

class Boss : public Character {
	bool aggrivate = false;

	Boss(GameState* gs);

	void init(int spawn_x, int spawn_y);

	void update(float dt);
	void draw();

	~Boss();

};




class MainCharacter : public Character {
	
	//Ability Timers
	class Timer* dashTimer, * dashCooldown,
		* jumpTimer1, * jumpCoolDown,*attackTimer1,*attackTimer2,*nextAttackWindow,
		*stuntTimer,*fluskUseCooldown;
	bool canDash = true;
	bool canJumpAgain = true;
	int FluskUses = 4;

	graphics::Brush text;

public:
	MainCharacter(GameState* gs, std::string name);

	void teleport(float x, float y);
	void damage(float dmg);
	void attack(float dmg);

	void regenerateHealth(float Health);
	void increaseHealth(float Health);
	void addFlaskUse();

	void init(int spawn_x, int spawn_y);

	void update(float dt);

	void draw();

	~MainCharacter();


};