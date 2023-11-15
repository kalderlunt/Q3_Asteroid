#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.h>

typedef struct Bullet{
    sfSprite* sprite;
    sfTexture* texture;
    sfVector2f velocity;

    float bulletRotation;

} Bullet;

int emptyLoaderBullets;
int numBullets;
int maxLoaderBullets;
float timeToReloadBulletInSecond;

sfClock* reloadClock;

///sfTexture* texture, sfVector2f position, sfVector2f velocity
void BulletInit(Bullet** bullet);

void BulletCreate(Bullet* bullets, sfVector2f SpawnPosition);

void BulletsUpdate(sfRenderWindow* window, sfSprite* ship, Bullet* bullets);

void BulletsDisplay(sfRenderWindow* window, Bullet* bullets);

void BulletsDestroy(Bullet* bullets);

#endif /*BULLET_H*/