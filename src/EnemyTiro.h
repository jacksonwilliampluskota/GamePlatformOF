#ifndef ENEMYTIRO_H
#define ENEMYTIRO_H
#include "ofApp.h"
class EnemyTiro
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
	string state = "ENEMY2_LEFT";
	int qtdAnimation;
	ofVec2f distanciaHeroEnemy;
	bool impulsar = false;

public:
	bool campoVisao = false;
	int vidas = 3;
	bool tryOne = false;
	bool onLeft = true, onRight = false;
	ofVec2f position;
	ofVec2f positionInit;
	bool morreu = false;
	float start_shoot;
	float shoot_interval;
	EnemyTiro();
	void setup(string path, float x, float y, int level[][40]);
	void update(float deltaTime, ofVec2f positionhero);
	void draw();
	ofVec2f getPosition();
	void setNewAnimation(string _state, int _qtdAnimation, int _counterlimit);
	float getSpeed();
	void setMorte();
	void dano(char tipo);
	int magnitudeSqr(ofVec2f vetor);
	void impulso(bool onLeft);
	bool time_to_shoot();
	~EnemyTiro();
};

#endif