#include "ofApp.h"
#include "World.h"
#include "Hero.h"
#include "Camera.h"
#include "Bala.h"
#include "level1.h"
#include "Enemy.h"
#include "EnemyTiro.h"
#include "Item.h"
#include <string>
#include <stdio.h>

string gameState;
Hero *hero;
Camera *camera;
level1 *fase1;
Enemy *enemy0;
Enemy *enemy1;
EnemyTiro *enemy4;
Enemy *enemy5;
EnemyTiro *enemy3;
EnemyTiro *enemy2;
EnemyTiro *enemy6;
vector<Bala> bullets;
vector<World> moedas;
vector<Item> itens;
ofVec2f moused;
ofVec4f mouseRelacaoMundo;
ofTrueTypeFont font;
ofTrueTypeFont fim;
ofImage bg;
ofImage alfa;
ofImage heart;
ofImage moedaImg;
ofImage flagImg;
ofVec2f flagposition;

//--------------------------------------------------------------
void ofApp::setup()
{
  soundGame.load("sound/game.wav");
  soundGame.play();
  soundGame.setLoop(true);
  font.loadFont("fonts/verdana.ttf", 15);
  fim.loadFont("fonts/verdana.ttf", 24);
  bg.load("images/inicioBg.png");
  alfa.load("images/alpha.png");
  heart.load("images/heart.png");
  moedaImg.load("images/coin.png");
  flagImg.load("images/flag.png");
  flagposition.set(608, 550);
  gameState = "start";

    for (int i = 0; i < 3; i++)
  {
    Item it;
    int x, y;

    if (i == 0)
    {
      x = 118;
      y = 610;
      it.setup("ITEM_BUMERANG", x, y, "boomerang");
    }
    if (i == 1)
    {
      x = 350;
      y = 610;
      it.setup("ITEM_ARCO", x, y, "arco");
    }
    if (i == 2)
    {
      x = 566;
      y = 556;
      it.setup("ITEM_DINAMITE", x, y, "dinamite");
    }

    itens.push_back(it);
  }

  for (int i = 0; i < 13; i++)
  {
    World m;
    int x, y;

    if (i == 0)
    {
      x = 138;
      y = 610;
    }
    if (i == 1)
    {
      x = 210;
      y = 570;
    }
    if (i == 2)
    {
      x = 242;
      y = 610;
    }
    if (i == 3)
    {
      x = 266;
      y = 610;
    }
    if (i == 4)
    {
      x = 428;
      y = 610;
    }
    if (i == 5)
    {
      x = 530;
      y = 566;
    }
    if (i == 6)
    {
      x = 546;
      y = 566;
    }
    if (i == 7)
    {
      x = 380;
      y = 546;
    }
    if (i == 8)
    {
      x = 324;
      y = 514;
    }
    if (i == 9)
    {
      x = 308;
      y = 514;
    }
    if (i == 10)
    {
      x = 224;
      y = 514;
    }
    if (i == 11)
    {
      x = 164;
      y = 514;
    }
    if (i == 12)
    {
      x = 64;
      y = 514;
    }

    m.moeda_setup("COIN", x, y);
    moedas.push_back(m);
  }

  fase1 = new level1();
  fase1->setup();

  hero = new Hero();
  hero->setup("images/body.png", 170, 550, fase1->leve1);

  enemy0 = new Enemy();
  enemy0->setup("images/body_enemy1.png", 80, 550, fase1->leve1, false);

  enemy1 = new Enemy();
  enemy1->setup("images/body_enemy1.png", 282, 550, fase1->leve1, true);

  enemy4 = new EnemyTiro();
  enemy4->setup("images/body_enemy2.png", 268, 490, fase1->leve1);

  enemy5 = new Enemy();
  enemy5->setup("images/body_enemy1.png", 86, 490, fase1->leve1, false);
  
  enemy3 = new EnemyTiro();
  enemy3->setup("images/body_enemy2.png", 440, 500, fase1->leve1);

  enemy2 = new EnemyTiro();
  enemy2->setup("images/body_enemy2.png", 362, 550, fase1->leve1);

  enemy6 = new EnemyTiro();
  enemy6->setup("images/body_enemy2.png", 30, 490, fase1->leve1);

  camera = new Camera();
  camera->setup(hero->getPosition());
}

//--------------------------------------------------------------
void ofApp::update()
{
  if (gameState == "start")
  {
  }
  else if (gameState == "game")
  {
    //std::cout << hero->enemyKill << std::endl;
    if (hero->vidas <= 0)
    {
      gameState = "end";
    }
    ofmoeda_update(ofGetLastFrameTime());
    ofitem_update(ofGetLastFrameTime());
    camera->update(hero->getPosition());
    hero->update(ofGetLastFrameTime());
    enemy0->update(ofGetLastFrameTime(), hero->getPosition());
    enemy1->update(ofGetLastFrameTime(), hero->getPosition());
    enemy4->update(ofGetLastFrameTime(), hero->getPosition());
    enemy5->update(ofGetLastFrameTime(), hero->getPosition());
    enemy3->update(ofGetLastFrameTime(), hero->getPosition());
    enemy2->update(ofGetLastFrameTime(), hero->getPosition());
    enemy6->update(ofGetLastFrameTime(), hero->getPosition());

    if (hero->colidiuEnemy(16, 16, enemy1->getPosition(), 12, 18))
    {
      std::cout << "colidiu com enemy 1" << endl;

      hero->dano();

      if (hero->vidas <= 0)
      {
        gameState = "end";
      }
    }

    if (hero->colidiuEnemy(16, 16, enemy4->getPosition(), 12, 18))
    {
      std::cout << "colidiu com enemy 1" << endl;

      hero->dano();

      if (hero->vidas <= 0)
      {
        gameState = "end";
      }
    }

    if (hero->colidiuEnemy(16, 16, enemy5->getPosition(), 12, 18))
    {
      std::cout << "colidiu com enemy 1" << endl;

      hero->dano();

      if (hero->vidas <= 0)
      {
        gameState = "end";
      }
    }

    if (hero->colidiuEnemy(16, 16, enemy0->getPosition(), 12, 18))
    {
      std::cout << "colidiu com enemy 0" << endl;

      hero->dano();

      if (hero->vidas <= 0)
      {
        gameState = "end";
      }
    }

    if (hero->colidiuEnemy(16, 16, enemy3->getPosition(), 12, 18))
    {
      std::cout << "colidiu com enemy 0" << endl;

      hero->dano();

      if (hero->vidas <= 0)
      {
        gameState = "end";
      }
    }

    if (hero->colidiuEnemy(16, 16, enemy2->getPosition(), 12, 18))
    {
      std::cout << "colidiu com enemy 1" << endl;

      hero->dano();

      if (hero->vidas <= 0)
      {
        gameState = "end";
      }
    }

    if (hero->colidiuEnemy(16, 16, enemy6->getPosition(), 12, 18))
    {
      std::cout << "colidiu com enemy 1" << endl;

      hero->dano();

      if (hero->vidas <= 0)
      {
        gameState = "end";
      }
    }

    if (enemy0->vidas <= 0 && !enemy0->morreu)
    {
      enemy0->setMorte();
      hero->enemyKill += 1;
    }

    if (enemy1->vidas <= 0 && !enemy1->morreu)
    {
      enemy1->setMorte();
      hero->enemyKill += 1;
    }

    if (enemy4->vidas <= 0 && !enemy4->morreu)
    {
      enemy4->setMorte();
      hero->enemyKill += 1;
    }
    else
    {
      if (enemy4->vidas > 0)
      {
        if (enemy4->campoVisao)
        {

          if (enemy4->time_to_shoot())
          {
            std::cout << "Atira" << endl;
            Bala bEnemy;
            std::cout << enemy4->getPosition() << endl;

            bEnemy.setup("SHOOT_ENEMY2", false, enemy4->getPosition(), enemy4->getSpeed(), 'R');
            bullets.push_back(bEnemy);
          }
        }
      }

    }

    if (enemy5->vidas <= 0 && !enemy5->morreu)
    {
      enemy5->setMorte();
      hero->enemyKill += 1;
    }


    if (enemy3->vidas <= 0 && !enemy3->morreu)
    {
      enemy3->setMorte();
      hero->enemyKill += 1;
    }
    else
    {

      if (enemy3->vidas > 0)
      {
        if (enemy3->campoVisao)
        {

          if (enemy3->time_to_shoot())
          {
            std::cout << "Atira" << endl;
            Bala bEnemy;
            std::cout << enemy3->getPosition() << endl;

            bEnemy.setup("SHOOT_ENEMY2", false, enemy3->getPosition(), enemy3->getSpeed(), 'R');
            bullets.push_back(bEnemy);
          }
        }
      }
    }

    if (enemy2->vidas <= 0 && !enemy2->morreu)
    {
      enemy2->setMorte();
      hero->enemyKill += 1;
    }
    else
    {
      if (enemy2->vidas > 0)
      {
        if (enemy2->campoVisao)
        {

          if (enemy2->time_to_shoot())
          {
            std::cout << "Atira" << endl;
            Bala bEnemy;
            std::cout << enemy2->getPosition() << endl;

            bEnemy.setup("SHOOT_ENEMY2", false, enemy2->getPosition(), enemy2->getSpeed(), 'R');
            bullets.push_back(bEnemy);
          }
        }
      }
    }

    if (enemy6->vidas <= 0 && !enemy6->morreu)
    {
      enemy6->setMorte();
      hero->enemyKill += 1;
    }
    else
    {

      if (enemy6->vidas > 0)
      {
        if (enemy6->campoVisao)
        {
          if (enemy6->time_to_shoot())
          {
            std::cout << "Atira" << endl;
            Bala bEnemy;
            std::cout << enemy6->getPosition() << endl;

            bEnemy.setup("SHOOT_ENEMY2", false, enemy6->getPosition(), enemy6->getSpeed(), 'R');
            bullets.push_back(bEnemy);
          }
        }
      }

    }

    bullet_update(ofGetLastFrameTime());

    if (hero->enemyKill >=7 && hero->moedas >= 13)
    {
      
      if (hero->colidiuEnemy(20, 44, flagposition, 12, 18))
      {
        gameState = "end";
      }

    }
  }
  else if (gameState == "end")
  {
    soundGame.stop();
  }
}

//--------------------------------------------------------------
void ofApp::draw()
{
  if (gameState == "start")
  {
    bg.draw(0, 0);
    alfa.draw(0, 0);
    ofSetBackgroundColor(17, 20, 27);
    ofSetColor(255, 255, 255);
		font.drawString("[APERTE QUALQUER TECLA PARA INICIAR O JOGO]", 250, 560);
		ofSetColor(255, 255, 255);
  }
  else if (gameState == "game")
  {
    ofSetBackgroundColor(17, 20, 27);
    ofPushMatrix();
    camera->draw();
    fase1->draw();
    hero->draw();
    enemy0->draw();
    enemy1->draw();
    enemy4->draw();
    enemy5->draw();
    enemy3->draw();
    enemy2->draw();
    enemy6->draw();

    if (hero->enemyKill >=7 && hero->moedas >= 13)
    {
      flagImg.draw(flagposition.x, flagposition.y);
    }

    for (int i = 0; i < bullets.size(); i++)
    {
      ofPushMatrix();
      bullets[i].draw();
      ofPopMatrix();
    }

    for (int i = 0; i < moedas.size(); i++)
    {
      moedas[i].moeda_draw();
    }

    for (int i = 0; i < itens.size(); i++)
    {
      itens[i].draw();
    }
    ofPopMatrix();

    heart.draw(25, 40);

    ofSetColor(255, 255, 255);
    font.drawString("X" + std::to_string(hero->vidas), 50, 60);
		ofSetColor(255, 255, 255);

    moedaImg.draw(100, 40);

    ofSetColor(255, 255, 255);
    font.drawString("X" + std::to_string(hero->moedas), 120, 60);
		ofSetColor(255, 255, 255);
  }
  else if (gameState == "end")
  {
    ofSetBackgroundColor(17, 20, 27);
    if (hero->vidas <= 0)
    {
      ofSetColor(255, 0, 0);
      fim.drawString("GAME OVER", 450, 384);
      ofSetColor(255, 255, 255);

      ofSetColor(255, 255, 255);
      font.drawString("Voce Morreu!", 470, 410);
      ofSetColor(255, 255, 255);
    }
    else
    {
      ofSetColor(0, 255, 0);
      fim.drawString("GAME OVER",450, 384);
      ofSetColor(255, 255, 255);

      ofSetColor(255, 255, 255);
      font.drawString("Voce Venceu!", 470, 410);
      ofSetColor(255, 255, 255);

    }
  }
}

void ofApp::bullet_update(float deltaTime)
{
  for (int i = 0; i < bullets.size(); i++)
  {

    if (bullets[i].fromPlayer)
    {
      bullets[i].update(deltaTime, hero->getPosition(), hero->onLeft);
      if (hero->checkCanShoo())
      {
        bullets[i].impulso(hero->onLeft, hero->angle);
      }
      int arrayTileX = ((bullets[i].position.x + bullets[i].sprite.getWidth()) / 40) * 2.5;
      int arrayTileY = ((bullets[i].position.y + bullets[i].sprite.getHeight()) / 40) * 2.5;

      if (bullets[i].colidiu(fase1->leve1[arrayTileY][arrayTileX]))
      {

        if (bullets[i]._tipo == 'B' || bullets[i]._tipo == 'E')
        {
          //continuar aqui
          bullets[i]._tipo = 'E';
        }
        else
        {
          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }
      }
      else
      {
        hero->shoot();
      }

      if (bullets[i]._tipo == 'A')
      {
        if (bullets[i].colidiuExplosao(16, 16, enemy0->getPosition(), 7, 4) && bullets[i].magFlecha < 7500)
        {
          enemy0->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy1->getPosition(), 7, 4) && bullets[i].magFlecha < 7500)
        {
          enemy1->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy4->getPosition(), 7, 4) && bullets[i].magFlecha < 7500)
        {
          enemy4->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy5->getPosition(), 7, 4) && bullets[i].magFlecha < 7500)
        {
          enemy5->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy3->getPosition(), 7, 4) && bullets[i].magFlecha < 7500)
        {
          enemy3->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy2->getPosition(), 7, 4) && bullets[i].magFlecha < 7500)
        {
          enemy2->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy6->getPosition(), 7, 4) && bullets[i].magFlecha < 7500)
        {
          enemy6->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].magFlecha > 7500)
        {
          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }
      }

      if (bullets[i]._tipo == 'E')
      {
        if (bullets[i].colidiuExplosao(12, 18, hero->getPosition(), 32, 32))
        {
          gameState = "end";
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy0->getPosition(), 32, 32) && !enemy0->morreu)
        {
          enemy0->setMorte();
          hero->enemyKill += 1;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy1->getPosition(), 32, 32)  && !enemy1->morreu)
        {
          enemy1->setMorte();
          hero->enemyKill += 1;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy4->getPosition(), 32, 32) && !enemy4->morreu)
        {
          enemy4->setMorte();
          hero->enemyKill += 1;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy5->getPosition(), 32, 32) && !enemy5->morreu)
        {
          enemy5->setMorte();
          hero->enemyKill += 1;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy3->getPosition(), 32, 32) && !enemy3->morreu)
        {
          enemy3->setMorte();
          hero->enemyKill += 1;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy2->getPosition(), 32, 32)  && !enemy2->morreu)
        {
          enemy2->setMorte();
          hero->enemyKill += 1;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy6->getPosition(), 32, 32) && !enemy6->morreu)
        {
          enemy6->setMorte();
          hero->enemyKill += 1;
        }

        if (bullets[i].paraAnimation)
        {
          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }
      }

      if (bullets[i]._tipo == 'G')
      {
        if (bullets[i].colidiuExplosao(16, 16, enemy0->getPosition(), 6, 4))
        {
          enemy0->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy1->getPosition(), 6, 4))
        {
          enemy1->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy4->getPosition(), 6, 4))
        {
          enemy4->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy5->getPosition(), 6, 4))
        {
          enemy5->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy3->getPosition(), 6, 4))
        {
          enemy3->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy2->getPosition(), 6, 4))
        {
          enemy2->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy6->getPosition(), 6, 4))
        {
          enemy6->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].volta)
        {
          //-----------------------------Alt e larg hero             alt e larg da bala
          if (bullets[i].colidiuExplosao(12, 18, hero->getPosition(), 6, 4))
          {
            std::cout << "foi" << std::endl;
            bullets.erase(bullets.begin() + i);
            hero->canshoot = true;
          }
        }
      }
    }
    else
    {
      bullets[i].update(deltaTime, hero->getPosition(), enemy2->onLeft);
      bullets[i].impulso(enemy2->onLeft, hero->angle);

      int arrayTileX = ((bullets[i].position.x + bullets[i].sprite.getWidth()) / 40) * 2.5;
      int arrayTileY = ((bullets[i].position.y + bullets[i].sprite.getHeight()) / 40) * 2.5;

      if (bullets[i]._tipo == 'R')
      {
        if (bullets[i].colidiuExplosao(12, 18, hero->getPosition(), 8, 8))
        {
          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->vidas -= 2;
        }
      }

      if (bullets[i].colidiu(fase1->leve1[arrayTileY][arrayTileX]))
      {
        std::cout << "foi" << std::endl;
        bullets.erase(bullets.begin() + i);
      }
    }
  }
}
void ofApp::ofmoeda_update(float deltaTime)
{
  for (int i = 0; i < moedas.size(); i++)
  {
    moedas[i].moeda_update(deltaTime);
    if (hero->colidiuEnemy(8, 8, moedas[i].positionCoin, 12, 18))
    {
      hero->moedas += 1;
      moedas.erase(moedas.begin() + i);
      std::cout << "moedas: " << hero->moedas << endl;
    }
  }
}

void ofApp::ofitem_update(float deltaTime)
{
  for (int i = 0; i < itens.size(); i++)
  {
    itens[i].update(deltaTime);
    if (hero->colidiuEnemy(10, 10, itens[i].positionItem, 12, 18))
    {
      if (itens[i].nomeItem == "boomerang")
      {
        hero->temBumerang = true;
      }

      if (itens[i].nomeItem == "arco")
      {
        hero->temArco = true;
      }

      if (itens[i].nomeItem == "dinamite")
      {
        hero->temDinamite = true;
      }

      itens.erase(itens.begin() + i);
    }
  }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
  if (gameState == "game")
  {
    if (key == OF_KEY_LEFT)
    {
      hero->onLeft = true;
      hero->onRight = false;
      hero->is_left_press = true;

      if (!hero->bomb)
      {

        hero->setNewAnimation("RUN_LEFT", 10, 5);
      }

      hero->tryOne = true;
    }

    if (key == OF_KEY_RIGHT)
    {
      hero->onRight = true;
      hero->onLeft = false;
      hero->is_right_press = true;

      if (!hero->bomb)
      {
        hero->setNewAnimation("RUN_RIGHT", 10, 5);
      }

      hero->tryOne = true;
    }

    if (key == OF_KEY_UP && !hero->bomb)
    {
      hero->is_up_press = true;

      if (hero->onRight)
      {
        hero->setNewAnimation("JUMP_RIGHT", 1, 1);
      }

      if (hero->onLeft)
      {
        hero->setNewAnimation("JUMP_LEFT", 1, 1);
      }

      hero->tryOne = true;
    }

    if (key == OF_KEY_DOWN)
      hero->is_down_press = true;

    if (key == ' ' && !hero->bomb && hero->temArco && !hero->pulando)
    {
      Bala b;
      hero->is_space_press = true;
      if (hero->onRight)
      {
        hero->setNewAnimation("BOW_RIGHT", 5, 3);
        b.setup("images/ARROW_RIGHT/0.png", true, hero->getPosition(), hero->getSpeed(), 'A');
      }

      if (hero->onLeft)
      {
        hero->setNewAnimation("BOW_LEFT", 5, 3);
        b.setup("images/ARROW_LEFT/0.png", true, hero->getPosition(), hero->getSpeed(), 'A');
      }

      hero->tryOne = true;

      if (hero->checkCanShoo())
      {
        std::cout << "deu para atira" << endl;
        bullets.push_back(b);
      }
    }

    if (key == 113 && hero->temDinamite)
    {
      hero->is_Q_press = true;
      hero->bomb = true;
      if (hero->onLeft)
      {
        hero->setNewAnimation("DINAMYT_LEFT", 1, 1);
      }

      if (hero->onRight)
      {
        hero->setNewAnimation("DINAMYT_RIGHT", 1, 1);
      }
    }

    if (key == 101 && !hero->bomb && hero->temBumerang)
    {
      Bala b;
      hero->is_E_press = true;
      hero->boomerang = true;
      if (hero->onLeft)
      {
        hero->setNewAnimation("BOW_LEFT", 5, 3);
        b.setup("BOOMERANG", true, hero->getPosition(), hero->getSpeed(), 'G');
      }

      if (hero->onRight)
      {
        hero->setNewAnimation("BOW_RIGHT", 5, 3);
        b.setup("BOOMERANG", true, hero->getPosition(), hero->getSpeed(), 'G');
      }

      if (hero->checkCanShoo())
      {
        bullets.push_back(b);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
  if (gameState == "start")
  {
    gameState = "game";
  }
  else if (gameState == "game")
  {

    if (key == OF_KEY_LEFT)
    {
      hero->is_left_press = false;
      hero->tryOne = false;

      if (!hero->bomb)
      {
        hero->setNewAnimation("IDDLE_LEFT", 4, 10);
      }
    }

    if (key == OF_KEY_RIGHT)
    {
      hero->is_right_press = false;
      hero->tryOne = false;

      if (!hero->bomb)
      {
        hero->setNewAnimation("IDDLE_RIGHT", 4, 10);
      }
    }

    if (key == OF_KEY_UP && !hero->bomb)
    {
      hero->is_up_press = false;
      hero->tryOne = false;

      if (hero->onRight)
      {
        hero->setNewAnimation("FALL_RIGHT", 1, 1);
      }

      if (hero->onLeft)
      {
        hero->setNewAnimation("FALL_LEFT", 1, 1);
      }
    }

    if (key == OF_KEY_DOWN)
    {
      hero->is_down_press = false;
    }

    if (key == ' ' && !hero->bomb)
    {
      hero->is_space_press = false;
      hero->tryOne = false;

      if (hero->onRight)
      {
        hero->setNewAnimation("IDDLE_RIGHT", 1, 1);
      }

      if (hero->onLeft)
      {
        hero->setNewAnimation("IDDLE_LEFT", 4, 10);
      }
    }

    if (key == 101 && !hero->bomb)
    {
      hero->is_E_press = false;
      hero->tryOne = false;
      hero->boomerang = false;

      if (hero->onRight)
      {
        hero->setNewAnimation("IDDLE_RIGHT", 1, 1);
      }

      if (hero->onLeft)
      {
        hero->setNewAnimation("IDDLE_LEFT", 4, 10);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
  if (gameState == "game")
  {
    moused.set(x, y);
    mouseRelacaoMundo = camera->posicaoRelacaoMundo(moused);
    hero->movedMouse(mouseRelacaoMundo.x, mouseRelacaoMundo.y);

    ofVec2f positionHero = hero->getPosition();

    if (hero->bomb)
    {

      if (mouseRelacaoMundo.x > positionHero.x)
      {
        hero->onRight = true;
        hero->onLeft = false;
        hero->setNewAnimation("DINAMYT_RIGHT", 1, 1);
        hero->tryOne = true;
      }

      if (mouseRelacaoMundo.x < positionHero.x)
      {
        hero->onLeft = true;
        hero->onRight = false;
        hero->setNewAnimation("DINAMYT_LEFT", 1, 1);
        hero->tryOne = true;
      }

      hero->tryOne = false;
    }
  }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
  if (gameState == "game")
  {
    if (hero->bomb)
    {
      Bala b;
      b.setup("images/DINAMYT/0.png", true, hero->getPosition(), hero->getSpeed(), 'B');
      hero->tryOne = true;

      if (hero->checkCanShoo())
      {
        std::cout << "aqui" << std::endl;
        bullets.push_back(b);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
  if (gameState == "game")
  {
    hero->bomb = false;
    hero->tryOne = false;

    if (hero->onRight)
    {
      hero->setNewAnimation("IDDLE_RIGHT", 1, 1);
    }

    if (hero->onLeft)
    {
      hero->setNewAnimation("IDDLE_LEFT", 4, 10);
    }
  }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
