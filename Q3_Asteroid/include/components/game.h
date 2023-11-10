#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.h>
#include "components/bullet.h"


typedef struct Game {
    sfRenderWindow* window;
    sfClock* deltaClock;
    sfSprite* ship;
    sfTexture* shipTexture;
    float shipRotation;
    Bullet* bullets;
    int numBullets;
    int maxBullets;
} Game;

void GameInit(Game* game);
void GameUpdate(Game* game);
void GameDisplay(Game* game);
void DestroyResources(Game* game);

#endif /*GAME_H*/