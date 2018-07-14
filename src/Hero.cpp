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
	gravidade.set(0, 100);

	imagemseta.load("images/seta.png");
	imagemseta.setAnchorPercent(0, 0.5f);

	pulando = false;
	is_left_press = false;
	is_right_press = false;
	is_up_press = false;
	is_down_press = false;
	is_space_press = false;
	is_Q_press = false;
	is_E_press = false;
}

void Hero::update(float deltaTime)
{
	ofVec2f forces;
	ofVec2f acceleration;
	ofVec2f accelSecs;

	forces = forces * speed;

	acceleration = forces / mass;
	int arrayTileX;
	if (onRight)
	{
		arrayTileX = ((position.x + sprite.getWidth()) / 40) * 2.5;
	}
	else
	{
		arrayTileX = ((position.x - sprite.getWidth()) / 40) * 2.5;
	}

	int arrayTileY = ((position.y + sprite.getHeight()) / 40) * 2.5;

	type = tiles[arrayTileY][arrayTileX];

	if (type == 16 || type == 18)
	{
		if (!pulando)
		{
			momentum.y = 0;
		}
		else
		{
			if (!tryOne)
			{
				if (onRight)
				{
					setNewAnimation("IDDLE_RIGHT", 4, 10);
				}

				if (onLeft)
				{
					setNewAnimation("IDDLE_LEFT", 4, 10);
				}
			}
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

	if (!bomb)
	{
		if (is_left_press && type != 18)
		{
			ofVec2f andar;
			andar.set(50, 0);
			momentum -= andar / mass;
		}

		if (is_right_press && type != 18)
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
	}

	if (!is_right_press && !is_left_press)
	{
		momentum.x = 0;
	}
}

void Hero::draw()
{
	ofPushMatrix();
	animation->draw(position.x, position.y);
	ofPopMatrix();

	if (bomb)
	{
		ofSetColor(255, 255, 255);
		ofDrawLine(position.x + 8, position.y + 8, mousePosition.x, mousePosition.y);
		ofSetColor(255, 255, 255);

		ofPushMatrix();
		ofTranslate(mousePosition.x, mousePosition.y);
		ofRotateZ(angle);
		imagemseta.draw(0, 0);
		ofPopMatrix();
	}
}

void Hero::jump()
{
	momentum.set(0, 0);
	ofVec2f impulse;
	impulse.set(0, -1200);
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

	if (canshoot)
	{
		canshoot = false;
	}
}

bool Hero::checkCanShoo()
{
	return canshoot;
}

ofVec2f Hero::getPosition()
{
	return position;
}

float Hero::getSpeed()
{
	return speed;
}

void Hero::movedMouse(int x, int y)
{
	mousePosition.set(x, y);
	vecMouse = mousePosition - position;
	getAngle(vecMouse);
}

ofVec2f Hero::vectorMouseHero()
{
	return vecMouse;
}

void Hero::getAngle(ofVec2f vetor)
{
	angle = toDegrees(atan2(vetor.y, vetor.x));
}

float Hero::toDegrees(float gd)
{
	return gd * 180 / PI;
}

bool Hero::colidiuEnemy(int width, int height, ofVec2f outraPosicao, int minhaWidth, int minhaHeight)
{

	if (position.x < outraPosicao.x + width &&
			outraPosicao.x < position.x + minhaWidth &&
			position.y < outraPosicao.y + height &&
			outraPosicao.y < position.y + minhaHeight)
	{
		return true;
	}

	return false;
}

void Hero::dano()
{
	momentum.set(0, 0);
	ofVec2f impulse;
	if (onRight)
		impulse.set(-35000, 0);
	if (onLeft)
		impulse.set(35000, 0);

	momentum += impulse / mass;

	vidas -= 1;
	cout << "afastou" << endl;
	cout << vidas << endl;
}

Hero::~Hero()
{
}
