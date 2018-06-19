#include "Animation.h"
#include <stdio.h>
Animation::Animation()
{
}

void Animation::setup(string state, int qtd)
{
  imageno = 0;
  counter = 0;
  counterlimit = 10;
  imageNum = qtd;
  for (int i = 0; i < imageNum; i++)
  {
    ofImage imagem;
    imagem.load("images/" + state + "/" + std::to_string(i) + ".png");
    image.push_back(imagem);
  }
  imagex = 0;
  imagey = 0;
}

void Animation::draw(int x, int y)
{
  ofTranslate(x, y);
  ofEnableAlphaBlending();
  image[imageno].draw(0, 0);
  ofDisableAlphaBlending();
  counter++;
  if (counter >= counterlimit)
  {
    counter = 0;
    imageno++;
    if (imageno >= imageNum)
      imageno = 0;
  }
}

Animation::~Animation()
{
}