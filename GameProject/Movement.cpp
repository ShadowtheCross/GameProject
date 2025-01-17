#include "Movement.h"
#include "Miscallenious.h"

Movement::Movement(GameState* gs, std::string name) : GameObject(gs, name) {

}

void Movement::init(float acc_x, float acc_y,
	float w, float h,
	float* player_x, float* player_y) {


	acceleration_x = acc_x*10e-4; acceleration_y = acc_y * 10e-4;
	width = w;
	height = h;
	
	current_x = player_x;
	current_y = player_y;
	overLapRadius = width + height / 2.0;
}


void Movement::moveY(float Time, Direction dir, float rate) {
	speed_y += Time * dir * acceleration_x *rate;
	int direction = sign(speed_y);
	if (GameObject::m_state->canGoAt(*current_x+width/2, *current_y + speed_y + height / 2 * direction ) &&
		GameObject::m_state->canGoAt(*current_x-width/2, *current_y + speed_y + height / 2 * direction)) {
		*current_y += speed_y;

		return;
	}
	speed_y = 0.0f;
}
void Movement::moveX(float Time, Direction dir, float rate) {
	speed_x += Time * dir * acceleration_x * rate;
	if (GameObject::m_state->canGoAt(*current_x + speed_x + width/ 2 * dir, *current_y + height/2)&&
		GameObject::m_state->canGoAt(*current_x + speed_x + width / 2 * dir, *current_y -height/2)) {
		*current_x += speed_x ;
		return;
	}
	speed_x = 0.0f;
}

void Movement::jump(float Time, float rate) {
	moveY(Time, Direction::Up, rate);
}

void Movement::dash(float Time, Direction dir, float rate) {
	moveX(Time, dir, rate);
}







void Movement::gravity(float Time) {
	moveY(Time, Direction::Down,1);

}




void Movement::update(float dt) {
	if (onFloor()) speed_y = 0;
	speed_x *= 0.9f;
}

bool Movement::onCeiling() {
	return !GameObject::m_state->canGoAt(*current_x, *current_y - height / 2 - 0.02f);
}




bool Movement::onFloor() {
	
	return !GameObject::m_state->canGoAt(*current_x +width/2, *current_y + height/2 +0.02f ) ||
		!GameObject::m_state->canGoAt(*current_x - width / 2, *current_y + height / 2 + 0.02f);
}

void Movement::draw() {
}

Movement::~Movement() {
}