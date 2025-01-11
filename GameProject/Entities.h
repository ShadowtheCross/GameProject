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

	void init(int spawn_x,int spawn_y);
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
protected:
	AnimationHandler* animations;
public:
	StaticEntity(GameState* gs, std::string name);

	void init(float x, float y,std::string TextureFolder);
	void update(float dt);
	void draw();
	void attack() {}
	void damage(float dmg) {}
	


	~StaticEntity();


};

class DecorativeDoor :public StaticEntity {
private:
    public:

		DecorativeDoor* declareAndInit(GameState* gs, float x, float y) {
			DecorativeDoor* temp = new DecorativeDoor(gs, "DecorativeDoor");
			temp->init(x, y);
			return temp;
		}


		DecorativeDoor(GameState* gs, std::string name);

		void init(float x, float y);
		void update(float dt);
		void draw();

    
	



	~DecorativeDoor();

};
class ExitDoor : public  DecorativeDoor {
private:
	bool opened = false;
	Timer NextLevelGo = Timer(0.5f, Timer::TIMER_ONCE);
	graphics::Brush Plain;
public:
	ExitDoor(GameState* gs);
	void init(float x, float y);
	void update(float dt);
	void draw();
	~ExitDoor();



};


class Chest :public StaticEntity {
private:
	bool opened = false;
public:

	Chest* declareAndInit(GameState* gs, float x, float y) {
		Chest* temp = new Chest(gs, "DecorativeDoor");
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
* Definition of the Character Class along with all the active Entities in Game
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
		float width, float height, float animation_width, float animation_height,
		int spawn_x, int spawn_y,
		float m_h);
	

	
	void update(float dt);

	


	virtual void attack() {}

	virtual void damage(float dmg) {}
	


	void kill();

	void draw();

	~Character();

};

class Enemy : public Character {
protected:
	bool alwaysAgro= false;
	bool aggrivate = false;
	float rate = 1;

public:
Enemy(GameState* gs, std::string name);

void init(float acc_x, float acc_y, float max_x, float max_y,
	std::string TexturesDirectory, std::string LoadScript,
	float width, float height, float animation_width, float animation_height,
	int spawn_x, int spawn_y,
	float m_h);
	void update(float dt);
	void draw();
	~Enemy();
	virtual void attack();
	virtual void damage(float dmg);

};




class Goblin : public Enemy {
private:
	Timer attackTimer1 =  Timer(.5f, Timer::TIMER_ONCE);
	Timer attackCooldown = Timer(2.0f, Timer::TIMER_ONCE);
	Timer dashTimer = Timer(0.4f, Timer::TIMER_ONCE);
	Timer dashCooldown = Timer(2.0f, Timer::TIMER_ONCE);
	Timer stunt = Timer(0.5f, Timer::TIMER_ONCE);
	Timer death = Timer(0.5f, Timer::TIMER_ONCE);
public:
	Goblin(GameState* gs);
	void init(int spawn_x, int spawn_y);
	void draw();
	void update(float dt);
	~Goblin();
	static Goblin* declareAndInit(GameState* gs, int spawn_x, int spawn_y) {
		Goblin* temp = new Goblin(gs);
		temp->init(spawn_x, spawn_y);
		return temp;
	}
	void attack();
	void damage(float dmg);
};


class Skeleton : public Enemy {
private:
	Timer death =  Timer(0.5f, Timer::TIMER_ONCE);
	Timer turnAroundTimer = Timer(1.0f, Timer::TIMER_ONCE);
	Timer attackTimer = Timer(1.0f, Timer::TIMER_ONCE);
	Timer blockTimer = Timer(0.5f, Timer::TIMER_ONCE);
	Timer stuntTimer = Timer(0.5f, Timer::TIMER_ONCE);
public:
	Skeleton(GameState* gs);
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

class Boss : public Enemy {
private:
	
	bool spawned1 = false, spawned2 = false;
	float spawnHealthTrigger1 = 0.0, spawnHealthTrigger2 = 0.0;
	Timer attackTimer =  Timer(1., Timer::TIMER_ONCE);
	Timer attackCooldown = Timer(1.5f, Timer::TIMER_ONCE);
	Timer deathTimer = Timer(2.0f, Timer::TIMER_ONCE);
public:
	Boss(GameState* gs);

	void init(int spawn_x, int spawn_y);

	void update(float dt);
	void draw();
	void attack(float dmg, float ripperEffect);
	void damage(float damage);

	~Boss();

};




class MainCharacter : public Character {
	
	//Ability Timers
	Timer dashTimer =  Timer(0.05f, Timer::TIMER_ONCE);
	Timer dashCooldown =  Timer(0.7f, Timer::TIMER_ONCE);
	Timer jumpTimer1 =  Timer(0.05, Timer::TIMER_ONCE);
	Timer jumpCoolDown =  Timer(.2f, Timer::TIMER_ONCE);
	Timer attackTimer1 =  Timer(0.45, Timer::TIMER_ONCE);
	Timer attackTimer2 =  Timer(0.45, Timer::TIMER_ONCE);
	Timer nextAttackWindow =  Timer(0.3f, Timer::TIMER_ONCE);
	Timer stuntTimer = Timer(0.5f, Timer::TIMER_ONCE);
	Timer fluskUseCooldown =  Timer(2.0f, Timer::TIMER_ONCE);
	Timer deathAnimation = Timer(1.2f, Timer::TIMER_ONCE);
	bool canDash = true;
	bool canJumpAgain = true,dead = false;
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