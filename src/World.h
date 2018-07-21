#ifndef WORLD_H
#define WORLD_H

#include "ofApp.h"
#include <string>
#include "Animation.h"
class World
{
private:
	Animation *animationCoin;

public:
	ofVec2f positionCoin;
	World();
	void moeda_setup(string state, int x, int y);
	void moeda_update(float deltaTime);
	void moeda_draw();
	~World();
};

#endif
