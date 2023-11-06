#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

typedef int bool;
#define true 1
#define false 0

int WINDOW_X = 1200;
int WINDOW_Y = 1200;

float delta = 0;

sfClock* deltaclock;
sfClock* animclock;
int nframe = 0;
int anim_time = 75; 

sfFont* font1;
sfRenderWindow* window;

int Delta() {
    sfTime dtime = sfClock_getElapsedTime(deltaclock);
    delta = sfTime_asMilliseconds(dtime);
    sfClock_restart(deltaclock);
}

int create() {
    WINDOW_X = sfVideoMode_getDesktopMode().width;
    WINDOW_Y = sfVideoMode_getDesktopMode().height;
    sfVideoMode mode = { WINDOW_X, WINDOW_Y, 32 };

    window = sfRenderWindow_create(mode, "SPOYO", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(window, 165);

    deltaclock = sfClock_create();
    animclock = sfClock_create();
    font1 = sfFont_createFromFile("Font/RetroGaming.ttf");

    
}

int main() {
    srand(time(0));
    create();


    sfMusic* music = sfMusic_createFromFile("asset/Music/Castelvania 2.wav");

    




    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        sfMusic_play(music);
        
        Delta();

        if (sfKeyboard_isKeyPressed(sfKeyEscape)) { sfRenderWindow_close(window); } //quit

        ////// DRAW /////
        sfTime atime = sfClock_getElapsedTime(animclock); //for animated frames
        int amseconds = sfTime_asMilliseconds(atime);
        if (amseconds >= anim_time) {
            nframe += 1;
            sfClock_restart(animclock);
        }
        sfRenderWindow_clear(window, sfTransparent);

        sfMusic_destroy(music);
        sfRenderWindow_display(window);
        /////////////////
    }

    sfClock_destroy(deltaclock);
    return 0;
}