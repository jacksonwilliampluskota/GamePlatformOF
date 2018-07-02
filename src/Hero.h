#ifndef HERO_H
#define HERO_H

#include "ofApp.h"
#include <string>
class Hero
{
private:
	ofImage sprite;
	ofVec2f position;
	ofVec2f gravidade;
	ofVec2f momentum;
	float mass = 15;
	float speed = 10;
	float maxSpeed = 40;
	bool pulando;
	int vidas;
	int tiles[40][40];
	int type;
	string state = "IDDLE_RIGHT";
	int qtdAnimation;
	ofVec2f mousePosition;
	ofImage imagemseta;

public:
	bool is_left_press, is_right_press, is_up_press, is_down_press, is_space_press, is_B_press;
	bool tryOne = false;
	bool onLeft = false, onRight = true;
	bool canshoot = true;
	bool bomb = false;
	Hero();
	void setup(string path, float x, float y, int level[][40]);
	void update(float deltaTime);
	void draw();
	void jump();
	void shoot();
	bool checkCanShoo();
	ofVec2f getPosition();
	void setNewAnimation(string _state, int _qtdAnimation, int _counterlimit);
	float getSpeed();
	void movedMouse(int x, int y);
	~Hero();
};

#endif