#include "ChunkLoader.h"


ChunkLoader::ChunkLoader(GameState* gs, std::string name) : GameObject(gs, name + "ObjectHandler") {

}

void ChunkLoader::init(int chunkSize) {
	int BlockSize = GameObject::m_state->getBlockSize();
	if (BlockSize > chunkSize) chunkSize = BlockSize;
}

void ChunkLoader::update(float dt) {

}

void ChunkLoader::draw() {
	float x = GameObject::m_state->getGlobalX();
	float y = GameObject::m_state->getGlobalY();
	std::list<GameObject*> *temp;
	for (int x_draw = x - 1; x_draw < x + Config::window_width; x_draw++) {
		for (int y_draw = y - 1; y_draw < y + Config::window_height; y_draw++) {
			int true_x = x_draw / chunkSize;
			int true_y = y_draw / chunkSize;
			temp = &(activeRenderer[true_x][true_y]);
			for (auto const i : *temp) {
				i->draw();
			}

		}
	}
}

void ChunkLoader::appendAt(float x, float y, GameObject* object) {
	int true_x = x / chunkSize;
	int true_y = y / chunkSize;
	activeRenderer[true_x][true_y].push_back(object);


}

