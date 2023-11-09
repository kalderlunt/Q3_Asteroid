#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "components/bullet.h"
#include "components/deltaTime.h"

#define MAX_BULLETS 100

void BulletInit(Ball* bullets, int* numBullets, int maxBullets, sfTexture* texture, sfVector2f position, sfVector2f velocity) {
    bullets = {
        .sprite = ;
        .texture = sfTexture_createFromFile("asset/Sprites/SpaceWar/space_ship.png", NULL);
        .velocity = 0;

        .numBullets = 0;
        .maxBullets = 0;
    };
}


void BulletCreate(Ball* bullets, int* numBullets, sfTexture* texture, sfVector2f position, sfVector2f velocity) {
    if (*numBullets < bullets->maxBullets) {
        bullets[*numBullets].sprite = sfSprite_create();

        sfSprite_setTexture(bullets[*numBullets].sprite, bullets->texture, sfTrue);
        sfSprite_setPosition(bullets[*numBullets].sprite, position);
        bullets[*numBullets].velocity = velocity;
        (*numBullets)++;
    }
}


void BulletsUpdate(sfRenderWindow* window, sfSprite* ship, Ball* bullets, int* numBullets, int maxBullets) {
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



    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        sfVector2f bulletPosition = sfSprite_getPosition(ship);
        sfVector2f bulletVelocity = { dir.x * 5.0f, dir.y * 5.0f };

        BulletCreate(bullets, &numBullets, bullets->texture, bulletPosition, bulletVelocity);
    }

    for (int i = 0; i < *numBullets; i++) {
        sfSprite_move(bullets[i].sprite, bullets[i].velocity);
    }

    if (*numBullets > maxBullets) {
        *numBullets = maxBullets;
    }
}


void BulletsDisplay(sfRenderWindow* window, Ball* bullets, int numBullets) {
    for (int i = 0; i < numBullets; i++) {
        sfRenderWindow_drawCircleShape(window, bullets[i].sprite, NULL);
    }
}


void BulletsDestroy(Ball* bullets, int numBullets) {
    for (int i = 0; i < numBullets; i++) {
        sfCircleShape_destroy(bullets[i].sprite);
        bullets->maxBullets --;
    }
}