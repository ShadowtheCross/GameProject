#pragma once
#include "GameLogic.h"
#include "GameState.h"


class Movement : public GameObject
{
	float speed_x = 0, speed_y = 0;
	float acceleration_x = 0, acceleration_y = 0;
	float max_speed_x = 0, max_speed_y = 0;
	float width = 0,  height= 0;
	float* current_x, * current_y;

	void limitX();
	void limitY();

	
public:
	Movement(GameState* gs, std::string name);

	void init(float acc_x, float acc_y,
		float max_x, float max_y,
		float w, float h,
		float* player_x, float* player_y);
	void moveDown(float Time);
	bool onFloor();
	void moveLeft(float Time);
	void moveRight(float Time);
	void moveUp(float Time);
	
	void gravity(float Time);

	void update(float dt);
	void draw();

	~Movement();
};