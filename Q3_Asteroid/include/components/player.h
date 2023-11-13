#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.h>

void PlayerInit(sfRenderWindow** window, sfSprite** ship, sfTexture** shipTexture, float* shipRotation);

void PlayerUpdate(sfRenderWindow* window, sfSprite* ship, sfTexture* shipTexture, float shipRotation);

//sfVector2i Player_GetMousePosition(sfVector2i MousePosition);


void PlayerDisplay(sfRenderWindow* window, sfSprite* ship);

void PlayerDestroy(sfSprite* ship, sfTexture* shipTexture);

#endif /*PLAER_H*/