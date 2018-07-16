#ifndef ENEMY_H
#define ENEMY_H
#include "ofApp.h"
class Enemy
{
private:
	ofImage sprite;
	ofVec2f gravidade;
	ofVec2f momentum;
	float mass = 1;
	float speed = 10;
	float maxSpeed = 40;
	int tiles[40][40];
	int type;
	string state = "ENEMY_LEFT";
	int qtdAnimation;
	ofVec2f distanciaHeroEnemy;

public:
	int vidas = 3;
	bool tryOne = false;
	bool onLeft = true, onRight = false;
	ofVec2f position;
	ofVec2f positionInit;
	bool morreu = false;
	Enemy();
	void setup(string path, float x, float y, int level[][40]);
	void update(float deltaTime, ofVec2f positionhero);
	void draw();
	ofVec2f getPosition();
	void setNewAnimation(string _state, int _qtdAnimation, int _counterlimit);
	float getSpeed();
	void setMorte();
	void dano(char tipo);
	int magnitudeSqr(ofVec2f vetor);
	~Enemy();
};

#endif