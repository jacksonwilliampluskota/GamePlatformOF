#include "level1.h"

level1::level1()
{
}

void level1::setup()
{
	tiles[0].load("images/bg0.png");
	tiles[1].load("images/bg1.png");
	tiles[2].load("images/bg2.png");
	tiles[3].load("images/bg3.png");
	tiles[4].load("images/bg4.png");
	tiles[5].load("images/bg5.png");
	tiles[6].load("images/bg6.png");
	tiles[7].load("images/bg7.png");
	tiles[8].load("images/bg8.png");
	tiles[9].load("images/bg9.png");
	tiles[10].load("images/bg10.png");
	tiles[11].load("images/bg11.png");
	tiles[12].load("images/bg12.png");
	tiles[13].load("images/bg13.png");
	tiles[14].load("images/bg14.png");
	tiles[15].load("images/bg15.png");
	tiles[16].load("images/chao.png");
	tiles[17].load("images/lado1.png");
}

void level1::draw()
{
	int type = 0;
	for (int row = 0; row < 40; row++)
	{
		for (int collunm = 0; collunm < 40; collunm++)
		{
			type = leve1[row][collunm];
			x = collunm * 16;
			y = row * 16;
			ofPushMatrix();
			ofTranslate(x, y);
			tiles[type].draw(0, 0);
			ofPopMatrix();
		}
	}
}

level1::~level1()
{
}
