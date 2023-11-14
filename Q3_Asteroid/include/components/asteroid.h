#ifndef ASTEROID
#define ASTEROID

#include <SFML/Graphics.h>

typedef struct Asteroid {
    sfSprite* sprite;
    sfTexture* texture;

    sfVector2f position;
    sfVector2f velocity;

    sfClock* respawnClock;
    float size;
} Asteroid;

int numAsteroids;
int maxAsteroids;



void AsteroidsInit(Asteroid** asteroids);

void AsteroidsCreate(Asteroid* asteroids);

void AsteroidsUpdate(sfRenderWindow* window, sfSprite* ship, Asteroid* asteroids);

void AsteroidsDisplay(sfRenderWindow* window, Asteroid* asteroids);

void AsteroidsDestroy(Asteroid* asteroids);

#endif /*ASTEROID*/