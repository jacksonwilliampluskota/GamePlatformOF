#include "Hero.h"
#include <stdio.h>
#include "Animation.h"

using namespace std;
Animation *animation;
Hero::Hero()
{
	animation = new Animation();
}

void Hero::setup(string path, float x, float y, int level[][40])
{
	qtdAnimation = 4;
	animation->setup(state, qtdAnimation, 10);
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			tiles[i][j] = level[i][j];
		}
	}

	//cout << tiles[39][39] << endl;
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
	int arrayTileX = ((position.x + sprite.getWidth()) / 40) * 2.5;
	int arrayTileY = ((position.y + sprite.getHeight()) / 40) * 2.5;

	type = tiles[arrayTileY][arrayTileX];
	if (type == 16)
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
	animation->draw(position.x, position.y);
}

void Hero::jump()
{
	momentum.set(0, 0);
	ofVec2f impulse;
	impulse.set(0, -400);
	momentum.y += impulse.y / mass;
}

void Hero::setNewAnimation(string _state, int _qtdAnimation, int _counterlimit)
{
	if (!tryOne)
	{
		animation->image.clear();
		animation->setup(_state, _qtdAnimation, _counterlimit);
	}
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
