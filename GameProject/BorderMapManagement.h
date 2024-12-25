#pragma once
#include "Config.h"
#include "GameLogic.h"
#include "GameState.h"
#include <iostream>
#include "unordered_map"

class BlockBorder : public GameObject {
	//top Line
    float a1 = 0 , b1 =0;
	//bottom Line
	float a2 =0 , b2 =0;


public:

	BlockBorder(GameState* gs, std::string name) : GameObject(gs, name) {

	}

	void init(float a1t, float b1t, float a2t, float b2t) {
		a1 = a1t;
		b1 = b1t ;
		a2 = a2t;
		b2 = b2t;

	}

	static BlockBorder * buildAndInit(GameState* gs, std::string name, float a1, float b1, float a2, float b2) {
		BlockBorder* temp = new BlockBorder(gs, name);
		temp->init(a1, b1, a2, b2);
		return temp;
	}
	
	bool canGoAt(float x,float y) {
		int basex =std::round(x);
		float y1 = a1 * (x-basex) + b1;//top line
		float y2 = a2 * (x-basex) + b2;//bottom line
		return y1 > y && y2 < y; //if (x,y) within block border of block x then true
	}

	bool containedWithin(float x,float y) {
		float y1 = a1 * x + b1;
		float y2 = a2 * x + b2;
		if (y1 > y && y2 < y) {
			return true;
		}
		return false;
	}
	void update() {

	}
	void draw() {

	}



	~BlockBorder() {

	}

};

