#include <SFML/Graphics.h>

#include "components/bullet.h"
#include "components/deltaTime.h"

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

void CreateSmallAsteroids(sfVector2f position, sfVector2f velocity, Asteroid** asteroids);

int CheckCollision(Bullet* bullets, Asteroid* asteroids);

void AsteroidRemove(int index, Asteroid** asteroids);

void HandleCollisions(Bullet* bullets, Asteroid** asteroids);

void AsteroidsUpdate(sfRenderWindow* window, sfSprite* ship, Asteroid** asteroids, Bullet** bullets);

void AsteroidsDisplay(sfRenderWindow* window, Asteroid** asteroids);

void AsteroidsDestroy(Asteroid** asteroids);

#endif /*ASTEROID*/