#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "components/bullet.h"
#include "components/deltaTime.h"

#define M_PI 3.14159265358979323846264338327950288



void BulletInit(Bullet** bullets) {
    emptyLoaderBullets = 0;
    maxLoaderBullets = 10;
    timeToReloadBulletInSecond = 3.0f;
    numBullets = maxLoaderBullets;

    // memory
    *bullets = malloc(maxLoaderBullets * sizeof(Bullet));
    
    if (*bullets == NULL) {
        printf("ERREUR #0040 | bullet initialization.\n");
        exit(EXIT_FAILURE);
    }

    (*bullets)->texture = sfTexture_createFromFile("asset/Sprites/SpaceWar/cannon.png", NULL);
    if ((*bullets)->texture == NULL) {
        printf("ERREUR #0043 | Unable to load texture for bullets.\n");
    }

    reloadClock = sfClock_create();

    for (int i = emptyLoaderBullets; i > numBullets; i--) {
        (*bullets)[i].texture = (*bullets)->texture;
    }
}


void BulletCreate(Bullet* bullets, sfVector2f SpawnPosition) {

    if (bullets != NULL) {
        if (numBullets > emptyLoaderBullets) {
            bullets[numBullets].sprite = sfSprite_create();

            if (bullets[numBullets].sprite != NULL) {
                sfSprite_setTexture(bullets[numBullets].sprite, bullets->texture, sfTrue);
                sfSprite_setPosition(bullets[numBullets].sprite, SpawnPosition);
                bullets[numBullets].velocity = bullets->velocity;

                sfSprite_setOrigin(bullets[numBullets].sprite, (sfVector2f) { 10, 9 });
                sfSprite_setRotation(bullets[numBullets].sprite, bullets[numBullets].bulletRotation);

                sfSprite_move(bullets[numBullets].sprite, bullets[numBullets].velocity);
                printf("PEW  |  PEW\n");

                numBullets --;
            }
            else {
                printf("ERREUR #0041 | Bullet sprite creation.\n");
            }
        }
        else {
            printf("ERREUR #00043 | Bullet limit exceeded.\n");
        }
    }
    else {
        printf("ERREUR #0049 | Pointeur NULL to BulletCreate.\n");
    }
}





void BulletsUpdate(sfRenderWindow* window, sfSprite* ship, Bullet* bullets) {
    // POSITION
    sfVector2i mousePosition = sfMouse_getPositionRenderWindow(window);
    sfVector2f shipPosition = sfSprite_getPosition(ship);

    sfVector2f dir;
    dir.x = mousePosition.x - shipPosition.x;    // direction x
    dir.y = mousePosition.y - shipPosition.y;    // direction y 

    float magnitude = (float)sqrt(dir.x * dir.x + dir.y * dir.y);      // norme

    if (magnitude > 0) {    // normalisation utile?
        (*bullets).velocity.x = (dir.x / magnitude) * dt;
        (*bullets).velocity.y = (dir.y / magnitude) * dt;
    }

    bullets->bulletRotation = (float)atan2f(dir.y, dir.x) * 180.0f / M_PI;


    if (numBullets <= emptyLoaderBullets) {
        sfTime reloadTime = sfClock_getElapsedTime(reloadClock);
        if (sfTime_asSeconds(reloadTime) > timeToReloadBulletInSecond) {  // reload every 500 ms
            numBullets = maxLoaderBullets;
            printf("            \n\nReload\n\n");
            sfClock_restart(reloadClock);
        }
    }
    else {
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            printf("%f  |  %f \n", bullets->velocity.x, bullets->velocity.y);
            sfVector2f bulletPosition = sfSprite_getPosition(ship);
            BulletCreate(bullets, bulletPosition);
        }
    }

    for (int i = emptyLoaderBullets; i > numBullets; i--) {
        sfSprite_move(bullets[i - 1].sprite, bullets[i - 1].velocity);
    }

    printf("%d  ", numBullets);

    if (numBullets < emptyLoaderBullets) {
        numBullets = emptyLoaderBullets;
    }
}


void BulletsDisplay(sfRenderWindow* window, Bullet* bullets){
    for (int i = emptyLoaderBullets; i > numBullets; i--) {
        sfRenderWindow_drawSprite(window, bullets[i].sprite, NULL);
    }
}


void BulletsDestroy(Bullet* bullets) {
    if (bullets != NULL) {
        for (int i = emptyLoaderBullets; i > numBullets; i--) {
            if (bullets[i].sprite != NULL) {
                sfSprite_destroy(bullets[i].sprite);
                bullets[i].sprite = NULL;
            }
            if (bullets[i].texture != NULL) {
                sfTexture_destroy(bullets[i].texture);
                bullets[i].texture = NULL;
            }
        }
    }
    free(bullets);
}