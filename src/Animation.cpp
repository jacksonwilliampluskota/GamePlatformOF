#include "Animation.h"
#include <stdio.h>
Animation::Animation()
{
}

void Animation::setup(string state, int qtd, int _counterlimit)
{
  imageno = 0;
  counter = 0;
  counterlimit = _counterlimit;
  imageNum = qtd;
  for (int i = 0; i < imageNum; i++)
  {
    ofImage imagem;
    imagem.load("images/" + state + "/" + std::to_string(i) + ".png");
    imagem.setAnchorPercent(0.5f, 0.5f);
    image.push_back(imagem);
  }
}

void Animation::draw(int x, int y)
{
  ofTranslate(x, y);
  ofEnableAlphaBlending();
  image[imageno].draw(0, 0);
  ofDisableAlphaBlending();

  if (imageNum > 1)
  {
    counter++;
    if (counter >= counterlimit)
    {
      counter = 0;
      imageno++;
      if (imageno >= imageNum)
        imageno = 0;
    }
  }
}

Animation::~Animation()
{
}