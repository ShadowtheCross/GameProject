#pragma once
#include "GameLogic.h"
#include "GameState.h"


class Movement : public GameObject
{
	float speed_x = 0, speed_y = 0;
	float acceleration_x = 0, acceleration_y = 0;
	float width = 0,  height= 0;
	float* current_x, * current_y;
	float overLapRadius;
	
public:

	enum Direction {
		Left = -1,
		Right = 1,
		Idle =0,
		Up =-1,
		Down= 1
	};
	
	Direction direction_x = Direction::Right;
	Direction ability_x = Direction::Right;

	Movement(GameState* gs, std::string name);

	void init(float acc_x, float acc_y,
		float w, float h,
		float* player_x, float* player_y);
//for exploration	
	
	void moveY(float Time, Direction dir, float rate = 1.0f);
	void moveX(float Time, Direction dir,float rate = 1.0f);
	void jump(float Time,float rate = 3.0f);
	void dash(float Time, Direction dir,float rate = 3.0f);

	bool falling() {
		return speed_y > 0;
	}
	bool rising() {
		return speed_y <= 0;
	}
	


	bool onCeiling();
	bool onFloor();
	void gravity(float Time);

	void update(float dt);
	void draw();

	~Movement();
};