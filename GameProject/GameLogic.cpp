#include "GameLogic.h"

class GameState;

GameObject::GameObject(GameState* gs, const std::string& name) {
	m_state = gs;
	m_name = name;

}