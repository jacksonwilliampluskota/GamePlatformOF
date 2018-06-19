#ifndef ANIMATION_H
#define ANIMATION_H

#include "ofApp.h"
#include <string>

class Animation
{
public:
  int imageNum;
  int imageno, counter, counterlimit, imagex, imagey;
  vector<ofImage> image;
  Animation();
  void setup(string state, int qtd);
  void draw(int x, int y);
  ~Animation();
};
#endif