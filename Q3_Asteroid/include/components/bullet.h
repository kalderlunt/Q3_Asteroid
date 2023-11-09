#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.h>

typedef struct Ball{
    sfSprite* sprite;
    sfTexture* texture;
    sfVector2f velocity;

    int numBullets;
    int maxBullets;
} Ball;

void BulletInit(Ball* bullets, int* numBullets, int maxBullets, sfTexture* texture, sfVector2f position, sfVector2f velocity);

void BulletCreate(Ball* bullets, int* numBullets, sfTexture* texture, sfVector2f position, sfVector2f velocity);

void BulletsUpdate(sfRenderWindow* window, sfSprite* ship, Ball* bullets, int* numBullets, int maxBullets);

//sfVector2i Bullet_GetMousePosition(sfVector2i MousePosition);


void BulletsDisplay(sfRenderWindow* window, Ball* bullets, int numBullets);

void BulletsDestroy(Ball* bullets, int numBullets);

#endif /*BULLET_H*/