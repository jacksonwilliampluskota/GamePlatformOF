#ifndef BALA_H
#define BALA_H

#include "ofApp.h"
#include <string>
class Bala
{
private:
	float speed;
	bool fromPlayer;
	ofImage sprite;
	ofVec2f momentum;
	float mass;
	char _tipo;
	enum tipos
	{
		A = 65,
		B = 98
	};

public:
	ofVec2f position;
	float width;
	Bala();
	void setup(string path, bool f_p, ofVec2f _position, float s, char tipo);
	void update(float deltaTime);
	void draw();
	void impulso(bool heroLeft);
	bool colidiu();
	~Bala();
};

#endif