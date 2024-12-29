#pragma once
#include "AnimationHandler.h"
#include "Movement.h"
#include "timer.h"


class MainCharacter : public GameObject {
	class AnimationHandler* animation;
	class Movement *mobilize;
	float true_x =0.0f, true_y=0.0f;
	//Ability Timers
	class Timer* dashTimer,*dashCooldown,
		*jumpTimer,*jumpCoolDown;
	

	

public:
	MainCharacter(GameState* gs, std::string name);


	void init(
		float acc_x, float acc_y, float max_x, float max_y,
		std::string TexturesDirectory, std::string LoadScript,
		float width, float height,
		int spawn_x, int spawn_y
	);

	void update(float dt);

	void draw();

	~MainCharacter();


};