#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "components/player.h"
#include "components/deltaTime.h"

#define M_PI 3.14159265358979323846264338327950288


float speed = 0.0f;


void PlayerInit(sfRenderWindow** window, sfSprite** ship, sfTexture** shipTexture, float* shipRotation) {

    *shipTexture = sfTexture_createFromFile("asset/Sprites/SpaceWar/space_ship.png", NULL);
    sfTexture_setSmooth(*shipTexture, 1);
    if (!*shipTexture) {
        exit(EXIT_FAILURE);
    }
    *ship = sfSprite_create();
    sfSprite_setTexture(*ship, *shipTexture, sfTrue);
    sfVector2f shipPosition = { sfRenderWindow_getSize(*window).x / 2, sfRenderWindow_getSize(*window).y / 2 };
    sfSprite_setPosition(*ship, shipPosition);
}

void PlayerUpdate(sfRenderWindow* window, sfSprite* ship, sfTexture* shipTexture, float shipRotation) {
    sfVector2i mousePosition = sfMouse_getPositionRenderWindow(window);
    sfVector2f shipPosition = sfSprite_getPosition(ship);
    
    sfVector2f dir;
    dir.x = mousePosition.x - shipPosition.x;    // direction x
    dir.y = mousePosition.y - shipPosition.y;    // direction y

    float magnitude = sqrt(dir.x * dir.x + dir.y * dir.y);      // norme

    if (magnitude > 0) {    // normalisation utile?
        dir.x /= magnitude;
        dir.y /= magnitude;
    }


    if(sfMouse_isButtonPressed(sfMouseRight)) {
        speed = 2.0f;
    }
    else {
        // Inertia
        speed *= 0.99f;
    }

    shipRotation = atan2f(dir.y, dir.x) * 180.0f / M_PI;
    
    sfSprite_setOrigin(ship, (sfVector2f) { 10, 9 });
    sfSprite_setRotation(ship, shipRotation);
    

    sfVector2u windowSize = sfRenderWindow_getSize(window);

    if (shipPosition.x > windowSize.x)
        shipPosition.x = 0;
    else if (shipPosition.x < 0)
        shipPosition.x = windowSize.x;

    if (shipPosition.y > windowSize.y)
        shipPosition.y = 0;
    else if (shipPosition.y < 0)
        shipPosition.y = windowSize.y;


    shipPosition.x += (dir.x / 10) * dt * speed;
    shipPosition.y += (dir.y / 10) * dt * speed;

    sfSprite_setPosition(ship, shipPosition);
}

void PlayerDisplay(sfRenderWindow* window, sfSprite* ship) {
    sfRenderWindow_drawSprite(window, ship, NULL);
}

void PlayerDestroy(sfSprite* ship, sfTexture* shipTexture) {
    sfTexture_destroy(shipTexture);
    sfSprite_destroy(ship);
}