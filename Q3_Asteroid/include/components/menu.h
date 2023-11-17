#include <SFML/Graphics.h>
#include <stdbool.h>

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

bool isMouseOverText(sfText* text, sfRenderWindow* window);

void MenuUpdate(sfEvent event, sfRenderWindow* window);

void MenuDisplay(sfRenderWindow* window);

void MenuDestroy();

#endif /*MENU*/