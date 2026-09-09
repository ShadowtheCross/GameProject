#include "GameLogic.h"
#include "GameState.h"
#include <iostream>


class SolidWallBorder : public GameObject {
	
	const bool isEmpty = true;
	SolidWallBorder(GameState* gs, std::string name);
	void init();

	void update();

	void draw();

	bool canGoTo(float x, float y);

	~SolidWallBorder();

};

class EmptyPath : public GameObject {
	
	const bool isEmpty = false;
	EmptyPath(GameState* gs, std::string name);
	void init();

	void update();

	void draw();

	bool canGoTo(float x, float y);

	~EmptyPath();


};
