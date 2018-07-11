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

	if (_tipo == A)
	{
		position.set(_position.x, _position.y + 8);
	}

	if (_tipo == B)
	{
		position.set(_position.x, _position.y - 8);
	}

	speed = s + 3;
	sprite.load(path);
	width = sprite.getWidth();

	momentum.set(0, 0);
	mass = 10;
	gravidade.set(0, 60);
}

void Bala::update(float deltaTime, ofVec2f vecmouseGet)
{

	if (_tipo == A)
	{
		ofVec2f forces;
		ofVec2f acceleration;
		ofVec2f accelSecs;

		forces += vecmouseGet.normalize() * speed;
		acceleration = forces / mass;

		accelSecs = acceleration * deltaTime;
		position += (momentum + accelSecs) * deltaTime;
		momentum += accelSecs;
	}

	cout << _tipo << endl;
	if (_tipo == B)
	{
		ofVec2f forces;
		ofVec2f acceleration;
		ofVec2f accelSecs;

		forces = forces * speed;

		acceleration = forces / mass;
		accelSecs = (acceleration + gravidade) * deltaTime;

		position += (momentum + accelSecs) * deltaTime;
		momentum += accelSecs;
	}
}

void Bala::draw()
{
	ofTranslate(position.x, position.y);
	sprite.draw(0, 0);
}

void Bala::impulso(bool heroLeft, float angleCanhao)
{
	if (_tipo == A)
	{
		momentum.set(0, 0);
		ofVec2f impulse;
		impulse.set(3000, 0);
		if (heroLeft)
		{
			impulse.set(-3000, 0);
		}

		momentum += impulse / mass;
	}

	if (_tipo == B)
	{
		momentum.set(0, 0);
		ofVec2f impulse;
		impulse.set(1000 * cos(angleCanhao * PI / 180), 1000 * sin(angleCanhao * PI / 180));
		momentum += impulse / mass;
	}
}

bool Bala::colidiu(int tile)
{
	//colide com bordas
	if (ofGetWidth() + position.x < 0 || position.x + width > ofGetWindowWidth())
		return true;

	if (position.y > ofGetWindowHeight())
		return true;

	if (tile == 16)
		return true;

	return false;
}

Bala::~Bala()
{
}
