#include "Hero.h"
#include <stdio.h>

using namespace std;

Hero::Hero()
{
}

void Hero::setup(string path, float x, float y, int level[][40])
{
	cout << level[0][0] << endl;
	sprite.load(path);
	position.set(x + sprite.getWidth(), y + sprite.getHeight());
	momentum.set(0, 0);
	gravidade.set(0, 40);
	pulando = false;
	is_left_press = false;
	is_right_press = false;
	is_up_press = false;
	is_down_press = false;
}

void Hero::update(float deltaTime)
{
	ofVec2f forces;
	ofVec2f acceleration;
	ofVec2f accelSecs;

	forces = forces * speed;

	acceleration = forces / mass;
	int arrayTileX = (position.x / 40) * 2.5;
	cout << arrayTileX << endl;

	if (position.y >= 300)
	{
		if (!pulando)
		{
			momentum.y = 0;
		}
		pulando = false;
	}
	else
	{
		acceleration += gravidade;
	}

	accelSecs = acceleration * deltaTime;
	position += (momentum + accelSecs) * deltaTime;
	momentum += accelSecs;

	if (momentum.x >= maxSpeed)
	{
		momentum.x = maxSpeed;
	}

	if (momentum.x <= maxSpeed * -1)
	{
		momentum.x = maxSpeed * -1;
	}

	if (is_left_press)
	{
		ofVec2f andar;
		andar.set(50, 0);
		momentum -= andar / mass;
	}

	if (is_right_press)
	{
		ofVec2f andar;
		andar.set(50, 0);
		momentum += andar / mass;
	}

	if (is_up_press)
	{
		if (!pulando)
		{
			jump();
			pulando = true;
		}
	}

	if (!is_right_press && !is_left_press)
	{
		momentum.x = 0;
	}
}

void Hero::draw()
{
	ofTranslate(position.x, position.y);
	sprite.draw(0, 0);
}

void Hero::jump()
{
	momentum.set(0, 0);
	ofVec2f impulse;
	impulse.set(0, -400);
	momentum.y += impulse.y / mass;
}

void Hero::shoot()
{
}

bool Hero::checkCanShoo()
{
	return false;
}

ofVec2f Hero::getPosition()
{
	return position;
}

float Hero::getSpeed()
{
	return speed;
}

Hero::~Hero()
{
}
