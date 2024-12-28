#include "Movement.h"
#include "Miscallenious.h"

Movement::Movement(GameState* gs, std::string name) : GameObject(gs, name) {
}

void Movement::init(float acc_x, float acc_y,
	float max_x, float max_y,
	float w, float h,
	float* player_x, float* player_y) {


	acceleration_x = acc_x; acceleration_y = acc_y ;
	max_speed_x = max_x; max_speed_y = max_y ;
	width = w;
	height = h;
	
	current_x = player_x;
	current_y = player_y;
}

void Movement::limitX() {
	if (abs(speed_x) > abs(max_speed_x)) {
		speed_x = sign(speed_x) * max_speed_x;
	}
}
void Movement::limitY() {
	if (abs(speed_y) > abs(max_speed_y)) {
		speed_y = sign(speed_y) * max_speed_y;
	}
}

void Movement::moveY(float Time, Direction dir, float rate) {
	speed_y = Time * dir * acceleration_x *rate;
	if (GameObject::m_state->canGoAt(*current_x, *current_y + speed_y + height / 2 * dir)) {
		*current_y += speed_y * dir;
		return;
	}
	speed_y = 0.0f;
}
void Movement::moveX(float Time, Direction dir, float rate) {
	speed_y = Time * dir * acceleration_x * rate;
	if (GameObject::m_state->canGoAt(*current_x + speed_y + width/ 2 * dir, *current_y )) {
		*current_x += speed_x * dir;
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
	moveY(Time, Direction::Down);

}




void Movement::update(float dt) {
	if (onFloor()) speed_y = 0;
	speed_x = speed_x * 0.1;
	std::cout << speed_x << " " << speed_y << "\n";
}






bool Movement::onFloor() {
	
	return !GameObject::m_state->canGoAt(*current_x, *current_y + height/2 +0.002f );
}

void Movement::draw() {
}

Movement::~Movement() {
}