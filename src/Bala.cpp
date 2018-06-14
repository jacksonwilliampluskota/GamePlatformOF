#include "Bala.h"

#include <stdio.h>

using namespace std;

Bala::Bala()
{
}

void Bala::setup(string path, bool f_p, ofVec2f _position, float s)
{
	fromPlayer = f_p;
	position.set(10, 10);

	speed = s + 3;
	sprite.load(path);
	width = sprite.getWidth();

	momentum.set(0, 0);
	mass = 0.1f;
}

void Bala::update(float deltaTime)
{

	ofVec2f forces;
	ofVec2f acceleration;
	ofVec2f accelSecs;

	forces = forces * speed;

	acceleration = forces / mass;

	accelSecs = acceleration * deltaTime;
	position += (momentum + accelSecs) * deltaTime;
	momentum += accelSecs;
}

void Bala::draw()
{
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	sprite.draw(0, 0);
	ofPopMatrix();
}

void Bala::impulso()
{
	momentum.set(0, 0);
	ofVec2f impulse;
	impulse.set(30, 0);
	momentum += impulse / mass;
}

Bala::~Bala()
{
}
