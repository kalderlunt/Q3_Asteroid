#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Graphics.h>

#include "components/game.h"

/*float delta = 0;
sfClock* deltaclock;
int Delta() {
    sfTime dtime = sfClock_getElapsedTime(deltaclock);
    delta = sfTime_asMilliseconds(dtime);
    sfClock_restart(deltaclock);
}*/
/*int create() {
    WINDOW_X = sfVideoMode_getDesktopMode().width;
    WINDOW_Y = sfVideoMode_getDesktopMode().height;
    sfVideoMode mode = { WINDOW_X, WINDOW_Y, 32 };

    window = sfRenderWindow_create(mode, "SPOYO", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(window, 165);

    deltaclock = sfClock_create();
    animclock = sfClock_create();
    font1 = sfFont_createFromFile("Font/RetroGaming.ttf");
}*/



int main() {
    srand(time(0));

    sfRenderWindow* window = NULL;
    
    sfClock* deltaClock;

    sfSprite* ship = NULL;
    sfTexture* shipTexture = NULL;
    float shipRotation = 0.0f;

    GameInit(&window, &deltaClock, &ship, &shipTexture, &shipRotation);

    Game(window, deltaClock, ship, shipTexture, shipRotation);
    
    DestroyResources(window, deltaClock, ship, shipTexture);

    return 0;
}