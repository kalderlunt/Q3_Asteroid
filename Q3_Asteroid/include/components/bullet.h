#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.h>

typedef struct Bullet{
    sfSprite* sprite;
    sfTexture* texture;
    sfVector2f velocity;

} Bullet;

///sfTexture* texture, sfVector2f position, sfVector2f velocity
void BulletInit(Bullet** bullets, int* numBullets, int* maxBullets);

void BulletCreate(Bullet* bullets, int* numBullets, int maxBullets, sfTexture* texture, sfVector2f position, sfVector2f velocity);

void BulletsUpdate(sfRenderWindow* window, sfSprite* ship, Bullet* bullets, int* numBullets, int maxBullets);

//sfVector2i Bullet_GetMousePosition(sfVector2i MousePosition);


void BulletsDisplay(sfRenderWindow* window, Bullet* bullets, int numBullets);

void BulletsDestroy(Bullet* bullets, int numBullets, int maxBullets);

#endif /*BULLET_H*/