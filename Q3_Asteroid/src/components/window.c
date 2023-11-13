#include <stdio.h>
#include <stdlib.h>
#include "components/window.h"


void WindowInit(sfRenderWindow** window) {
    int windowWidth = sfVideoMode_getDesktopMode().width / 2;
    int windowHeight = sfVideoMode_getDesktopMode().height / 2;
    // Window initialization
    sfVideoMode mode = { windowWidth, windowHeight, 32 };
    *window = sfRenderWindow_create(mode, "Asteroid", sfClose, NULL);
    sfRenderWindow_setFramerateLimit(*window, 60);

    if (!*window) {
        // Failure management
        exit(EXIT_FAILURE);
    }
}

void WindowDisplay(sfRenderWindow* window) {
    sfRenderWindow_display(window);
}

void WindowDestroy(sfRenderWindow* window) {
    sfRenderWindow_destroy(window);
}