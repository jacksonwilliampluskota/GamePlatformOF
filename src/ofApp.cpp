#include "ofApp.h"
#include "World.h"
#include "Hero.h"
#include "Camera.h"
#include "Bala.h"
#include "level1.h"
#include "Enemy.h"
#include "EnemyTiro.h"
#include <string>
#include <stdio.h>

string gameState;
World *mundo;
Hero *hero;
Camera *camera;
level1 *fase1;
Enemy *enemy1;
EnemyTiro *enemy2;
ofImage bg;
vector<Bala> bullets;
ofVec2f moused;
ofVec4f mouseRelacaoMundo;
//--------------------------------------------------------------
void ofApp::setup()
{
  gameState = "start";
  mundo = new World();
  mundo->moeda_setup("COIN", 138, 610);
  fase1 = new level1();
  fase1->setup();
  hero = new Hero();
  hero->setup("images/body.png", 170, 550, fase1->leve1);
  enemy1 = new Enemy();
  enemy1->setup("images/body_enemy1.png", 370, 550, fase1->leve1);
  enemy2 = new EnemyTiro();
  enemy2->setup("images/body_enemy2.png", 470, 550, fase1->leve1);
  camera = new Camera();
  camera->setup(hero->getPosition());
  bg.load("images/download.jpg");
}

//--------------------------------------------------------------
void ofApp::update()
{
  if (gameState == "start")
  {
  }
  else if (gameState == "game")
  {
    if (hero->vidas <= 0)
    {
      gameState = "end";
    }
    mundo->moeda_update(ofGetLastFrameTime());
    camera->update(hero->getPosition());
    hero->update(ofGetLastFrameTime());
    enemy1->update(ofGetLastFrameTime(), hero->getPosition());
    enemy2->update(ofGetLastFrameTime(), hero->getPosition());

    if (hero->colidiuEnemy(16, 16, enemy1->getPosition(), 12, 18))
    {
      std::cout << "colidiu com enemy 1" << endl;

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

    if (enemy1->vidas <= 0)
    {
      enemy1->setMorte();
    }

    if (enemy2->vidas <= 0)
    {
      enemy2->setMorte();
    }
    else
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

    bullet_update(ofGetLastFrameTime());
  }
  else if (gameState == "end")
  {
  }
}

//--------------------------------------------------------------
void ofApp::draw()
{
  if (gameState == "start")
  {
  }
  else if (gameState == "game")
  {
    ofSetBackgroundColor(17, 20, 27);
    ofPushMatrix();
    camera->draw();
    fase1->draw();
    //bg.draw(100, 100);
    hero->draw();
    enemy1->draw();
    enemy2->draw();
    mundo->moeda_draw();
    for (int i = 0; i < bullets.size(); i++)
    {
      ofPushMatrix();
      bullets[i].draw();
      ofPopMatrix();
    }
    ofPopMatrix();
  }
  else if (gameState == "end")
  {
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
        if (bullets[i].colidiuExplosao(16, 16, enemy1->getPosition(), 7, 4))
        {
          enemy1->dano(bullets[i]._tipo);

          std::cout << "foi" << std::endl;
          bullets.erase(bullets.begin() + i);
          hero->canshoot = true;
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy2->getPosition(), 7, 4))
        {
          enemy2->dano(bullets[i]._tipo);

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

        if (bullets[i].colidiuExplosao(16, 16, enemy1->getPosition(), 32, 32))
        {
          enemy1->setMorte();
        }

        if (bullets[i].colidiuExplosao(16, 16, enemy2->getPosition(), 32, 32))
        {
          enemy2->setMorte();
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
        if (bullets[i].colidiuExplosao(16, 16, enemy1->getPosition(), 6, 4))
        {
          enemy1->dano(bullets[i]._tipo);

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

    if (key == ' ' && !hero->bomb)
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

    if (key == 113)
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

    if (key == 101 && !hero->bomb)
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
