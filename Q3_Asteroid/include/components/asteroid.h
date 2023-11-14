#ifndef ASTEROID
#define ASTEROID

#include <SFML/Graphics.h>

typedef struct Asteroid {
    sfSprite* sprite;
    sfTexture* texture;

    sfVector2f position;
    sfVector2f velocity;

    float size;
} Asteroid;

int numAsteroids;
int maxAsteroids;

sfClock* respawnClock;
float timeToSpawnAsteroidInSecond;


void AsteroidsInit(Asteroid** asteroids);

void AsteroidsCreate(sfRenderWindow* window, Asteroid* asteroids);

void AsteroidsUpdate(sfRenderWindow* window, sfSprite* ship, Asteroid* asteroids);

void AsteroidsDisplay(sfRenderWindow* window, Asteroid* asteroids);

void AsteroidsDestroy(Asteroid* asteroids);

#endif /*ASTEROID*/