#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "components/bullet.h"
#include "components/deltaTime.h"

#define M_PI 3.14159265358979323846264338327950288



void BulletInit(Bullet** bullets, int* numBullets, int* maxBullets, float* bulletRotation) {
    *numBullets = 10;
    *maxBullets = 10;


    // memory
    *bullets = malloc(*maxBullets * sizeof(Bullet));
    
    if (*bullets == NULL) {
        printf("ERREUR #0040 | bullet initialization.\n");
        exit(EXIT_FAILURE);
    }




    sfTexture* texture = sfTexture_createFromFile("asset/Sprites/SpaceWar/cannon.png", NULL);
    if (texture == NULL) {
        printf("ERREUR #0043 | Unable to load texture for bullets.\n");
    }


    for (int i = 0; i < *maxBullets; i++) {
        (*bullets)[i].texture = texture;

        (*bullets)[i].inMagazine = 0;
        (*bullets)[i].toReload = *maxBullets;
        //printf("Bullet to Reload %d\n", (*bullets)[i].toReload);
        (*bullets)[i].reloadClock = sfClock_create();
    }
}


void BulletCreate(Bullet* bullets, int* numBullets, int maxBullets, sfTexture* texture, sfVector2f position, sfVector2f velocity, float bulletRotation) {

    if (bullets != NULL && numBullets != NULL && texture != NULL) {
        if (*numBullets < maxBullets) {


            if (bullets[*numBullets].inMagazine <= 0) {
                sfTime reloadTime = sfClock_getElapsedTime(bullets[*numBullets].reloadClock);
                if (sfTime_asMilliseconds(reloadTime) > 500 && bullets[*numBullets].inMagazine < bullets[*numBullets].toReload) {  // Recharge toutes les 500 ms
                    bullets[*numBullets].inMagazine = bullets[*numBullets].toReload;
                    printf("Reload\n");
                    printf("Reload\n");
                    printf("Reload\n");
                    printf("Reload\n");
                    sfClock_restart(bullets[*numBullets].reloadClock);
                }
            }


            if (bullets[*numBullets].inMagazine > 0) {
                bullets[*numBullets].sprite = sfSprite_create();

                if (bullets[*numBullets].sprite != NULL) {
                    sfSprite_setTexture(bullets[*numBullets].sprite, texture, sfTrue);
                    sfSprite_setPosition(bullets[*numBullets].sprite, position);
                    bullets[*numBullets].velocity = velocity;

                    sfSprite_setOrigin(bullets[*numBullets].sprite, (sfVector2f) { 10, 9 });
                    sfSprite_setRotation(bullets[*numBullets].sprite, bulletRotation);

                    sfSprite_move(bullets[*numBullets].sprite, bullets[*numBullets].velocity);
                    printf("PEW  |  PEW\n");
                    (*numBullets)++;
                    bullets[*numBullets].inMagazine--;
                }
                else {
                    printf("ERREUR #0041 | Bullet sprite creation.\n");
                }
            }
            else {
                printf("ERREUR #00042 | No bullets left in the magazine. Wait for reload.\n");
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





void BulletsUpdate(sfRenderWindow* window, sfSprite* ship, Bullet* bullets, int* numBullets, int maxBullets, float bulletRotation) {
    // POSITION
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


    bulletRotation = atan2f(dir.y, dir.x) * 180.0f / M_PI;

    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        sfVector2f bulletPosition = sfSprite_getPosition(ship);
        sfVector2f bulletVelocity = { dir.x, dir.y };
        printf("%f  |  %f\n", bulletVelocity.x, bulletVelocity.y);

        BulletCreate(bullets, numBullets, maxBullets, bullets->texture, bulletPosition, bulletVelocity, bulletRotation);
    }

    for (int i = 0; i < *numBullets; i++) {
        sfSprite_move(bullets[i].sprite, bullets[i].velocity);
    }

    printf("%d", *numBullets);

    if (*numBullets > maxBullets) {
        *numBullets = maxBullets;
    }
}


void BulletsDisplay(sfRenderWindow* window, Bullet* bullets, int numBullets) {
    for (int i = 0; i < numBullets; i++) {
        sfRenderWindow_drawSprite(window, bullets[i].sprite, NULL);
    }
}


void BulletsDestroy(Bullet* bullets, int numBullets, int maxBullets) {
    if (bullets != NULL) {
        for (int i = 0; i < numBullets; i++) {
            if (bullets[i].sprite != NULL) {
                sfSprite_destroy(bullets[i].sprite);
                bullets[i].sprite = NULL;
            }
            if (bullets[i].texture != NULL) {
                sfTexture_destroy(bullets[i].texture);
                bullets[i].texture = NULL;
            }
            sfClock_destroy(bullets[i].reloadClock);
        }
    }
    free(bullets);
}