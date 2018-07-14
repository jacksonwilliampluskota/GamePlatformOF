#ifndef ENEMY_H
#define ENEMY_H
#include "ofApp.h"
class Enemy
{
private:
	ofImage sprite;
	ofVec2f gravidade;
	ofVec2f momentum;
	float mass = 15;
	float speed = 10;
	float maxSpeed = 30;
	int tiles[40][40];
	int type;
	string state = "ENEMY_LEFT";
	int qtdAnimation;

public:
	int vidas = 3;
	bool tryOne = false;
	bool onLeft = true, onRight = false;
	ofVec2f position;
	ofVec2f positionInit;
	bool morreu = false;
	Enemy();
	void setup(string path, float x, float y, int level[][40]);
	void update(float deltaTime);
	void draw();
	ofVec2f getPosition();
	void setNewAnimation(string _state, int _qtdAnimation, int _counterlimit);
	float getSpeed();
	void setMorte();
	void dano(char tipo);
	~Enemy();
};

#endif