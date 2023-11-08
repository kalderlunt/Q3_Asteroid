#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.h>

void InitGame(sfRenderWindow** window);

void DestroyResources(sfRenderWindow* window);

void Game(sfRenderWindow* window);

#endif /*GAME_H*/