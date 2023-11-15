#include <SFML/Graphics.h>

#ifndef ASTEROID
#define ASTEROID
#define MAX_MEMORY_ASTEROIDS 1000


typedef struct Asteroid {
    sfSprite* sprite;
    sfTexture* texture;

    sfVector2f position;
    sfVector2f velocity;

    float angle;
    float speed;

    float size;
} Asteroid;

int numAsteroids;
int maxAsteroids;
int memoryMaxAsteroids;

sfClock* respawnClock;
float timeToSpawnAsteroidInSecond;


void AsteroidsInit(Asteroid** asteroids);

void AsteroidsCreate(sfRenderWindow* window, Asteroid** asteroids);

void AsteroidsUpdate(sfRenderWindow* window, sfSprite* ship, Asteroid** asteroids);

void AsteroidsDisplay(sfRenderWindow* window, Asteroid** asteroids);

void AsteroidsDestroy(Asteroid** asteroids);

#endif /*ASTEROID*/