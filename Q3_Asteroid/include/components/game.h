#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.h>

#include "components/deltaTime.h"
#include "components/window.h"
#include "components/bullet.h"
#include "components/asteroid.h"
#include "components/player.h"


typedef struct Game {
    sfRenderWindow* window;
    sfClock* deltaClock;
    sfSprite* ship;
    sfTexture* shipTexture;
    float shipRotation;
    Bullet* bullets;

    Asteroid* asteroids;
} Game;

void GameInit(Game* game);
void GameUpdate(Game* game);
void GameDisplay(Game* game);
void DestroyResources(Game* game);

void GameLoop(Game* game);

#endif /*GAME_H*/