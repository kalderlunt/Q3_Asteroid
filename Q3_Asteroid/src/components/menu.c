#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SFML/Window.h"
#include "components/menu.h"




void MenuInit() {
	menuState = MENU;
}

void MenuUpdate(Game* game) {
	switch (menuState)
	{
	case MENU:
		if (sfKeyboard_isKeyPressed(sfKeyEnter))
			menuState = GAME;
		break;

	case GAME:
		GameUpdate(game);
		break;

	case DIFFICULTY:
		break;

	case GAMEOVER:
		break;

	default:
		break;
	}
	
}

void MenuDisplay(Game* game) {
	switch (menuState)
	{
	case MENU:
		break;
	
	case GAME:
		GameDisplay(game);
		break;

	case DIFFICULTY:
		break;
	
	case GAMEOVER:
		break;

	default:
		break;
	}
}

void MenuDestroy() {

}