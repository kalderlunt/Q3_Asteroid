#include <stdio.h>
#include <stdlib.h>
#include "components/window.h"
#include "components/game.h"


void InitGame(sfRenderWindow** window) {
    InitWindow(window);
}

void DestroyResources(sfRenderWindow* window) {
    // Liberating resources
    DestroyWindow(window);
}

void Game(sfRenderWindow* window) {
    // Main game loop
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
        }

        // Game update logic
        if (sfKeyboard_isKeyPressed(sfKeyEscape)) { sfRenderWindow_close(window); } // quit
        //UpdateLogic();

        // Clear screen
        sfRenderWindow_clear(window, sfTransparent);

        // Draw your elements
            //UpdateDraw();

        // Display screen
        sfRenderWindow_display(window);
    }
}