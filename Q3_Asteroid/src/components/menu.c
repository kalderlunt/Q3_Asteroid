#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "SFML/Window.h"
#include "components/menu.h"



sfFont* font;
sfText* textPlay;
sfText* textQuit;


void MenuInit() {
    font = sfFont_createFromFile("Font/RetroGaming.ttf");

    // Play and Quit text
    textPlay = sfText_create();
    sfText_setString(textPlay, "Play");
    sfText_setFont(textPlay, font);
    sfText_setCharacterSize(textPlay, 30);
    sfText_setPosition(textPlay, (sfVector2f) { 100, 100 });

    textQuit = sfText_create();
    sfText_setString(textQuit, "Quit");
    sfText_setFont(textQuit, font);
    sfText_setCharacterSize(textQuit, 30);
    sfText_setPosition(textQuit, (sfVector2f) { 100, 150 });
}

bool isMouseOverText(sfText* text, sfRenderWindow* window) {
    sfVector2i mouse = sfMouse_getPositionRenderWindow(window);
    sfFloatRect textBounds = sfText_getGlobalBounds(text);
    return sfFloatRect_contains(&textBounds, mouse.x, mouse.y);
} 

void MenuUpdate(sfEvent event, sfRenderWindow* window) {
    if (sfKeyboard_isKeyPressed(sfKeyEnter)) {
        printf("Play Keyboard clicked!\n");
        menuState = GAME;
    }
    if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
        printf("Quit Keyboard clicked!\n");
        sfRenderWindow_close(window);
    }

    /*if (event.type == sfEvtMouseButtonPressed) {
        if (isMouseOverText(textPlay, window)) {
            printf("Play clicked!\n");
            menuState = GAME;
        }

        if (isMouseOverText(textQuit, window)) {
            printf("Quit clicked!\n");
            sfRenderWindow_close(window);
        }
    }*/
}


void MenuDisplay(sfRenderWindow* window) {
    sfRenderWindow_drawText(window, textPlay, NULL);
    sfRenderWindow_drawText(window, textQuit, NULL);
}

void MenuDestroy() {
    sfFont_destroy(font);
    sfText_destroy(textPlay);
    sfText_destroy(textQuit);
}