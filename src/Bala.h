#ifndef BALA_H
#define BALA_H

#include "ofApp.h"
#include <string>
class Bala
{
private:
	float speed;
	bool fromPlayer;
	ofVec2f momentum;
	float mass;
	enum tipos
	{
		A = 65,
		B = 'B',
		E = 'E'
	};
	ofVec2f gravidade;

public:
	bool paraAnimation = false;
	bool tryOnemoreTime = true;
	char _tipo;
	ofImage sprite;
	ofVec2f position;
	float width;
	Bala();
	void setup(string path, bool f_p, ofVec2f _position, float s, char tipo);
	void update(float deltaTime, ofVec2f vecmouseGet);
	void draw();
	void impulso(bool heroLeft, float angleCanhao);
	bool colidiu(int tile);
	~Bala();
};

#endif