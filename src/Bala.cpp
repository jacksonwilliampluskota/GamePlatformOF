#include "Bala.h"

#include <stdio.h>

using namespace std;

Bala::Bala()
{
}

void Bala::setup(string path, bool f_p, ofVec2f _position, float s, char tipo)
{
	_tipo = tipo;
	fromPlayer = f_p;
	position.set(_position.x, _position.y + 8);

	speed = s + 3;
	sprite.load(path);
	width = sprite.getWidth();

	momentum.set(0, 0);
	mass = 0.1f;
}

void Bala::update(float deltaTime)
{

	if (_tipo == A)
	{
	}
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
	if (_tipo == A)
	{
	}
	ofTranslate(position.x, position.y);
	sprite.draw(0, 0);

	if (_tipo == B)
	{
	}
}

void Bala::impulso(bool heroLeft)
{
	if (_tipo == A)
	{
	}
	momentum.set(0, 0);
	ofVec2f impulse;
	impulse.set(30, 0);

	if (heroLeft)
	{
		impulse.set(-30, 0);
	}

	momentum += impulse / mass;

	if (_tipo == B)
	{
	}
}

bool Bala::colidiu()
{
	//colide com bordas
	if (ofGetWidth() + position.x < 0 || position.x + width > ofGetWindowWidth())
		return true;

	if (position.y > ofGetWindowHeight())
		return true;

	return false;
}

Bala::~Bala()
{
}
