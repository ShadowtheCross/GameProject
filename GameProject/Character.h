#pragma once
#include "AnimationHandler.h"
#include "Movement.h"

class Character :  virtual public AnimationHandler, virtual public Movement {
	float true_x, true_y;
public:
	Character(GameState* gs, std::string name);
	void init(
		float acc_x, float acc_y, float max_x, float max_y,
		std::string TexturesDirectory, std::string LoadScript,
		float width, float height,
		int spawn_x, int spawn_y
	);
	void update(float dt);

	void draw();

	~Character();


};