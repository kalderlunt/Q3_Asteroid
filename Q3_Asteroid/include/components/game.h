#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.h>

void GameInit(sfRenderWindow** window, sfSprite** ship, sfTexture** shipTexture, float* shipRotation);

void GameUpdate(sfRenderWindow* window, sfSprite* ship, sfTexture* shipTexture, float shipRotation);

void GameDisplay(sfRenderWindow* window, sfSprite* ship, sfTexture* shipTexture);

void DestroyResources(sfRenderWindow* window, sfSprite* ship, sfTexture* shipTexture);

void Game(sfRenderWindow* window, sfSprite* ship, sfTexture* shipTexture, float shipRotation);

#endif /*GAME_H*/