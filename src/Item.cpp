#include "Item.h"
#include <stdio.h>

Item::Item()
{
}

void Item::setup(string state, int x, int y, string nome)
{
    nomeItem = nome;
	animationCoin = new Animation();
	positionItem.set(x, y);
	animationCoin->setup(state, 1, 100);
}

void Item::update(float deltaTime)
{
}

void Item::draw()
{
	ofPushMatrix();
	animationCoin->draw(positionItem.x, positionItem.y);
	ofPopMatrix();
}

Item::~Item()
{
}
