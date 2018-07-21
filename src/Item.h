#ifndef ITEM_H
#define ITTEM_H

#include "ofApp.h"
#include <string>
#include "Animation.h"
class Item
{
private:
	Animation *animationCoin;

public:
	ofVec2f positionItem;
    string nomeItem;
	Item();
	void setup(string state, int x, int y, string nome);
	void update(float deltaTime);
	void draw();
	~Item();
};

#endif
