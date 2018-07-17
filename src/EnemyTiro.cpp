#include "EnemyTiro.h"
#include <stdio.h>
#include "Animation.h"

using namespace std;
Animation *animationEnemyTiro;

EnemyTiro::EnemyTiro()
{
  animationEnemyTiro = new Animation();
}

void EnemyTiro::setup(string path, float x, float y, int level[][40])
{
  qtdAnimation = 5;
  animationEnemyTiro->setup(state, qtdAnimation, 10);
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

void EnemyTiro::update(float deltaTime, ofVec2f positionhero)
{

  if (!morreu)
  {
    ofVec2f forces;
    ofVec2f acceleration;
    ofVec2f accelSecs;
    forces = forces * speed;

    acceleration = forces / mass;

    distanciaHeroEnemy = positionhero - position;
    int mag = magnitudeSqr(distanciaHeroEnemy);
    //cout << mag << endl;

    if (mag < 4500)
    {

      if (onLeft)
      {

        if (tryOne)
        {
          setNewAnimation("ENEMY2_LEFT", 5, 10);
          tryOne = false;
        }
      }

      if (onRight)
      {

        if (tryOne)
        {
          setNewAnimation("ENEMY2_RIGHT", 5, 10);
          tryOne = false;
        }
      }
    }
    else
    {
      tryOne = true;
    }

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
  }
}

int EnemyTiro::magnitudeSqr(ofVec2f vetor)
{
  return vetor.x * vetor.x + vetor.y * vetor.y;
}

void EnemyTiro::draw()
{

  if (!morreu)
  {
    ofPushMatrix();
    animationEnemyTiro->draw(position.x, position.y);
    ofPopMatrix();
  }
}

ofVec2f EnemyTiro::getPosition()
{
  return position;
}

void EnemyTiro::setNewAnimation(string _state, int _qtdAnimation, int _counterlimit)
{
  if (tryOne)
  {
    animationEnemyTiro->image.clear();
    animationEnemyTiro->setup(_state, _qtdAnimation, _counterlimit);
  }
}

float EnemyTiro::getSpeed()
{
  return speed;
}
void EnemyTiro::setMorte()
{
  position.set(0, 0);
  morreu = true;
  animationEnemyTiro->image.clear();
}

void EnemyTiro::dano(char tipo)
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

void EnemyTiro::impulso(bool onLeft)
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

EnemyTiro::~EnemyTiro()
{
}
