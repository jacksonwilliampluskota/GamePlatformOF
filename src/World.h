#ifndef WORLD_H
#define WORLD_H

#include "ofApp.h"
#include <string>
class World
{
private:
ofVec2f positionCoin;
public:
	World();
	void moeda_setup(string state,int x, int y);
	void moeda_update(float deltaTime);
	void moeda_draw();
	~World();
};

#endif
