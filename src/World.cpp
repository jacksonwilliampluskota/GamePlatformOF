#include "World.h"
#include <stdio.h>

World::World()
{
	std::cout << "inciou" << std::endl;
}

void World::moeda_setup(string state, int x, int y)
{
	animationCoin = new Animation();
	positionCoin.set(x, y);
	animationCoin->setup(state, 4, 8);
}

void World::moeda_update(float deltaTime)
{
}

void World::moeda_draw()
{
	ofPushMatrix();
	animationCoin->draw(positionCoin.x, positionCoin.y);
	ofPopMatrix();
}

World::~World()
{
}
