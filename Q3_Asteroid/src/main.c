#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Graphics.h>

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

void InitWindow(sfRenderWindow** window) {
    int windowWidth = sfVideoMode_getDesktopMode().width / 2;
    int windowHeight = sfVideoMode_getDesktopMode().height / 2;
    // Window initialization
    sfVideoMode mode = { windowWidth, windowHeight, 32 };
    *window = sfRenderWindow_create(mode, "Asteroid", sfClose, NULL);

    if (!*window) {
        // Failure management
        exit(EXIT_FAILURE);
    }
}
void InitGame(sfRenderWindow** window) {
    InitWindow(window);
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


void ReleaseWindow(sfRenderWindow* window) {
    sfRenderWindow_destroy(window);
}
void ReleaseResources(sfRenderWindow* window) {
    // Liberating resources
    ReleaseWindow(window);
}


int main() {

    sfRenderWindow* window = NULL;

    InitGame(&window);

    Game(window);

    ReleaseResources(window);

    return 0;
}