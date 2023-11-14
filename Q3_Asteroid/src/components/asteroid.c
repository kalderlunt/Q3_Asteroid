#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SFML/Window.h"
#include "components/asteroid.h"
#include "components/deltaTime.h"

#define M_PI 3.14159265358979323846264338327950288

void AsteroidsInit(Asteroid** asteroids) {

    numAsteroids = 0;
    maxAsteroids = 10;
    
    *asteroids = (Asteroid*)malloc(sizeof(Asteroid) * maxAsteroids);

    for (int i = 0; i < maxAsteroids; i++) {
        (*asteroids)[i].sprite = sfSprite_create();
        (*asteroids)[i].texture = sfTexture_createFromFile("asset/Sprites/SpaceWar/asteroids_1.png", NULL);
        (*asteroids)[i].size = 1.0f;
    }
    
    respawnClock = sfClock_create();
    timeToSpawnAsteroidInSecond = 2.0f;
}

void AsteroidsCreate(sfRenderWindow* window, Asteroid* asteroids) {
    if (asteroids != NULL) {
        if (numAsteroids < maxAsteroids) {

            asteroids[numAsteroids].position.x = rand() % sfRenderWindow_getSize(window).x;
            asteroids[numAsteroids].position.y = rand() % sfRenderWindow_getSize(window).y;
            asteroids[numAsteroids].velocity.x = (float)(rand() % 6);
            asteroids[numAsteroids].velocity.y = (float)(rand() % 6);
            
            sfSprite_setTexture(asteroids[numAsteroids].sprite, asteroids[numAsteroids].texture, sfTrue);
            sfSprite_setOrigin(asteroids[numAsteroids].sprite, (sfVector2f) { 62 / 2, 46 / 2 });
            sfSprite_setPosition(asteroids[numAsteroids].sprite, asteroids[numAsteroids].position);

            printf("\n\nSPAWN | Asteroid has spawned.\n\n");

            numAsteroids++;
        }
    }
    else {
        printf("ERREUR #0059 | Pointeur NULL to AsteroidsCreate.\n");
    }
}

void AsteroidsUpdate(sfRenderWindow* window, sfSprite* ship, Asteroid* asteroids) {
    
    sfTime elapsed = sfClock_getElapsedTime(respawnClock);
    float seconds = sfTime_asSeconds(elapsed);

    if (seconds > timeToSpawnAsteroidInSecond) {
        if (numAsteroids < maxAsteroids) {
            AsteroidsCreate(window, asteroids);
            sfClock_restart(respawnClock);
        }
    }
    for (int i = 0; i < numAsteroids; i++) {

        // Bounce off the window borders |/\| wraparound
        sfVector2u windowSize = sfRenderWindow_getSize(window);

        if (asteroids[i].position.x < 0 || asteroids[i].position.x > windowSize.x)
            asteroids[i].velocity.x = -asteroids[i].velocity.x;

        if (asteroids[i].position.y < 0 || asteroids[i].position.y > windowSize.y)
            asteroids[i].velocity.y = -asteroids[i].velocity.y;

        sfSprite_move(asteroids[i].sprite, asteroids[i].velocity);
    }
}

void AsteroidsDisplay(sfRenderWindow* window, Asteroid* asteroids) {
    for (int i = 0; i < numAsteroids; i++) {
        sfRenderWindow_drawSprite(window, asteroids[i].sprite, NULL);
    }
}

void AsteroidsDestroy(Asteroid* asteroids) {
    if (asteroids != NULL) {
        for (int i = 0; i < numAsteroids; i++) {
            sfSprite_destroy(asteroids[i].sprite);
            sfTexture_destroy(asteroids[i].texture);
        }
        sfClock_destroy(respawnClock);
        free(asteroids);
    }
    else {
        printf("ERREUR #0058 | Pointeur NULL to AsteroidsDestroy.\n");
    }
}
