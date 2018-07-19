#include "Enemy.h"
#include <stdio.h>
#include "Animation.h"

using namespace std;
Animation *animationEnemy;

Enemy::Enemy()
{
  animationEnemy = new Animation();
}

void Enemy::setup(string path, float x, float y, int level[][40])
{
  qtdAnimation = 5;
  animationEnemy->setup(state, qtdAnimation, 10);
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
  positionInit.set(x + sprite.getWidth(), y + sprite.getHeight());
  momentum.set(0, 0);
  gravidade.set(0, 100);
}

void Enemy::update(float deltaTime, ofVec2f positionhero)
{

  if (!morreu)
  {
    ofVec2f forces;
    ofVec2f acceleration;
    ofVec2f accelSecs;

    distanciaHeroEnemy = positionhero - position;
    int mag = magnitudeSqr(distanciaHeroEnemy);
    //cout << mag << endl;

    if (mag < 5200)
    {

      if (!impulsar)
      {
        impulso(onLeft);
        impulsar = true;
      }

      if (onLeft)
      {
        forces += distanciaHeroEnemy.normalize() * speed;

        if (tryOne)
        {
          setNewAnimation("ENEMY_LEFT", 5, 10);
          tryOne = false;
        }

        if (forces.x >= 0)
        {
          onLeft = false;
          onRight = true;
          tryOne = true;
        }
      }

      if (onRight)
      {
        forces += distanciaHeroEnemy.normalize() * speed;

        if (tryOne)
        {
          setNewAnimation("ENEMY_RIGHT", 5, 10);
          tryOne = false;
        }

        if (forces.x <= 0)
        {
          onLeft = true;
          onRight = false;
          tryOne = true;
        }
      }
    }
    else
    {
      momentum.x = 0;
      impulsar = false;
    }

    acceleration = forces / mass;
    int arrayTileX = ((position.x + sprite.getWidth()) / 40) * 2.5;
    int arrayTileY = ((position.y + sprite.getHeight()) / 40) * 2.5;

    type = tiles[arrayTileY][arrayTileX];
    if (type == 16 || type == 18)
    {
      momentum.y = 0;
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
  }
}

int Enemy::magnitudeSqr(ofVec2f vetor)
{
  return vetor.x * vetor.x + vetor.y * vetor.y;
}

void Enemy::draw()
{

  if (!morreu)
  {
    ofPushMatrix();
    animationEnemy->draw(position.x, position.y);
    ofPopMatrix();
  }
}

ofVec2f Enemy::getPosition()
{
  return position;
}

void Enemy::setNewAnimation(string _state, int _qtdAnimation, int _counterlimit)
{
  if (tryOne)
  {
    animationEnemy->image.clear();
    animationEnemy->setup(_state, _qtdAnimation, _counterlimit);
  }
}

float Enemy::getSpeed()
{
  return speed;
}
void Enemy::setMorte()
{
  position.set(0, 0);
  morreu = true;
  animationEnemy->image.clear();
}

void Enemy::dano(char tipo)
{

  if (tipo == 'G')
  {
    vidas -= 1;
  }

  if (tipo == 'A')
  {
    vidas -= 2;
  }

  cout << "retirou vida do enemy" << endl;
  cout << vidas << endl;
}

void Enemy::impulso(bool onLeft)
{
  momentum.set(0, 0);
  ofVec2f impulse;
  impulse.set(15, 0);
  if (onLeft)
  {
    impulse.set(-15, 0);
  }

  momentum += impulse / mass;
}

Enemy::~Enemy()
{
}
