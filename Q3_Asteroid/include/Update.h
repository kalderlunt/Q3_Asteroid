#pragma once
#ifndef UPDATE_H
#define UPDATE_H

#include "SFML/Graphics.h"


typedef int bool;
#define false 0
#define true 1


bool gameover;

int widthWindow, heightWindow;
int x, y;
int fruitX, fruitY;
int speedSnake, score;
int nbTail;
int tailX[100], tailY[100];


int winWidth, winHeight;
int size;


enum eDirection {
    STOP = 0,
    UP,
    DOWN,
    RIGHT,
    LEFT
};
enum eDirection dir, prevDir;


/*void Update(int x, int y, int tailX[], int tailY[], int nbTail
    , int widthWindow, int heightWindow, int fruitX, int fruitY
    , int score, int speedSnake, bool gameover, const char charGameOver);*/

void Setup();




void Update(char charGameOver, sfRenderWindow* window, sfRectangleShape* snake, sfCircleShape* fruit);

void Input();

void MovementTail();

void MovementPlayer(sfRenderWindow* window, sfRectangleShape* snake);

void Collision(char charGameOver);

void EatFruit();
void CollisionSpawnFruit();




void Draw(char charGameOver, sfRenderWindow* window, sfRectangleShape* snake, sfCircleShape* fruit);

void DrawGame();

void DrawSnake(sfRenderWindow* window, sfRectangleShape* snake);

void DrawFruit(sfRenderWindow* window, sfCircleShape* fruit);

void DrawScore();

void DrawDeath(char charGameOver);


#endif/*UPDATE_H*/