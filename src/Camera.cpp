#include "Camera.h"
#include <stdio.h>

using namespace std;
Camera::Camera()
{
}

void Camera::setup(ofVec2f positionHero)
{
	view.setTranslation(
			(ofGetWindowWidth() / size) / scale - positionHero.x,
			(ofGetWindowHeight() / size) / scale - positionHero.y,
			0);
	view.scale(scale, scale, 1);
}

void Camera::update(ofVec2f positionHero)
{
	ofVec4f heroRelacaoMundo;
	heroRelacaoMundo.set(positionHero.x, positionHero.y, 0, 1);
	heroRelacaoMundo = heroRelacaoMundo * view.getInverse();

	float vinteCincoCinco = ofGetWindowWidth() - (ofGetWindowWidth() * 0.75f);
	float setentaCincoCinco = ofGetWindowWidth() - (ofGetWindowWidth() * 0.25f);

	/* cout << heroRelacaoMundo << endl;
	cout << x << endl; */

	if (heroRelacaoMundo.x > 0 && heroRelacaoMundo.x <= x && heroRelacaoMundo.y > 0 /* && heroRelacaoMundo.y <= y */)
	{
		view = ofMatrix4x4();
		view.setTranslation(
				(ofGetWindowWidth() / size) / scale - positionHero.x,
				(ofGetWindowHeight() / size) / scale - positionHero.y,
				0);
		view.scale(scale, scale, 1);
	}
}

ofVec4f Camera::posicaoRelacaoMundo(ofVec2f positionObject)
{
	ofVec4f objRelacaoMundo;
	objRelacaoMundo.set(positionObject.x, positionObject.y, 0, 1);
	objRelacaoMundo = objRelacaoMundo * view.getInverse();

	return objRelacaoMundo;
}

void Camera::draw()
{
	ofMultMatrix(view);
}

Camera::~Camera()
{
}
