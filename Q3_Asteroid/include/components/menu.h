#include <SFML/Graphics.h>

#include "components/game.h"

#ifndef _MENU_
#define _MENU_

typedef enum {
    MENU = 0,
    GAME,
    DIFFICULTY,
    GAMEOVER
} Scene;


int menuState;

void MenuInit();

void MenuUpdate(Game* game);

void MenuDisplay(Game* game);

void MenuDestroy();

#endif /*MENU*/