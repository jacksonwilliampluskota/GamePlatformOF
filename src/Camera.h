#ifndef CAMERA_H
#define CAMERA_H

#include "ofApp.h"
class Camera
{
private:
	ofMatrix4x4 view;
	float scale = 3.0f;
	float size = 2.0f;
	int x = 40 * 16;
	int y = 40 * 16;

public:
	Camera();
	void setup(ofVec2f positionHero);
	void update(ofVec2f positionHero);
	ofVec4f posicaoRelacaoMundo(ofVec2f positionObject);
	void draw();
	~Camera();
};

#endif