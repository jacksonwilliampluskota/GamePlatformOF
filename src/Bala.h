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

public:
	ofVec2f position;
	float width;
	Bala();
	void setup(string path, bool f_p, ofVec2f _position, float s);
	void update(float deltaTime);
	void draw();
	void impulso();
	~Bala();
};

#endif