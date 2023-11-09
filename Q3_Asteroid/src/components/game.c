#include <stdio.h>
#include <stdlib.h>
#include "components/game.h"
#include "components/window.h"
#include "components/player.h"
#include "components/deltaTime.h"


void GameInit(sfRenderWindow** window, sfClock** deltaClock, sfSprite** ship, sfTexture** shipTexture, float* shipRotation) {
    DeltaInit(deltaClock);

    WindowInit(window);
    PlayerInit(window, ship, shipTexture, shipRotation);
}

void GameUpdate(sfRenderWindow* window, sfClock* deltaClock, sfSprite* ship, sfTexture* shipTexture, float shipRotation) {
    DeltaTime(deltaClock);
    PlayerUpdate(window, ship, shipRotation);
}

void GameDisplay(sfRenderWindow* window, sfSprite* ship, sfTexture* shipTexture) {
    
    sfRenderWindow_clear(window, sfTransparent);

    PlayerDisplay(window, ship);
    
    WindowDisplay(window);
}

void DestroyResources(sfRenderWindow* window, sfClock* deltaClock, sfSprite* ship, sfTexture* shipTexture) {
    // Liberating resources

    PlayerDestroy(ship, shipTexture);
    DeltaDestroy(deltaClock);
    WindowDestroy(window);
}

void Game(sfRenderWindow* window, sfClock* deltaClock, sfSprite* ship, sfTexture* shipTexture, float shipRotation) {
    // Main game loop
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
        }

        GameUpdate(window, deltaClock, ship, shipTexture, shipRotation, shipRotation);

        GameDisplay(window, ship, shipTexture);        
    }
}