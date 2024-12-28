#include "Movement.h"
#include "Miscallenious.h"

Movement::Movement(GameState* gs, std::string name) : GameObject(gs, name) {
}

void Movement::init(float acc_x, float acc_y,
	float max_x, float max_y,
	float w, float h,
	float* player_x, float* player_y) {


	acceleration_x = acc_x*1e-3; acceleration_y = acc_y * 1e-3;
	max_speed_x = max_x*1e-3; max_speed_y = max_y * 1e-3;
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

void Movement::moveDown(float Time) {
	float down = Time * 0.05f;
	if ( GameObject::m_state->canGoAt(*current_x,*current_y + speed_y + height/2 + down)  ){
		*current_y += down;
	}
	
}

void Movement::moveUp(float Time) {
	float up =  - Time * 0.05f;
	if (GameObject::m_state->canGoAt(*current_x, *current_y + speed_y - height / 2 + up)) {
		*current_y += up;
	}
	
}

void Movement::gravity(float Time) {
	speed_y += acceleration_y * Time;
	if (GameObject::m_state->canGoAt(*current_x, *current_y + speed_y + height / 2)) {
		*current_y += speed_y;
	}
	else {
		speed_y = 0.0f;
	}

}



void Movement::moveLeft(float Time) {
	speed_x -= acceleration_x * Time;
	limitX();
	if (GameObject::m_state->canGoAt(*current_x - width/2 + speed_x, *current_y)) {
		*current_x += speed_x;
	}
	
}
void Movement::moveRight(float Time) {
	speed_x += acceleration_x * Time;
	limitX();
	if (GameObject::m_state->canGoAt(*current_x + width / 2 + speed_x, *current_y)) {
		*current_x += speed_x;
	}

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