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
    memoryMaxAsteroids = MAX_MEMORY_ASTEROIDS;

    *asteroids = (Asteroid*)malloc(sizeof(Asteroid) * maxAsteroids);

    timeToSpawnAsteroidInSecond = 2.0f;
    respawnClock = sfClock_create();
}

void AsteroidsCreate(sfRenderWindow* window, Asteroid** asteroids) {
    if ((*asteroids) != NULL) {
        if (numAsteroids < memoryMaxAsteroids) {
            (*asteroids)[numAsteroids].sprite = sfSprite_create();
            (*asteroids)[numAsteroids].texture = sfTexture_createFromFile("asset/Sprites/SpaceWar/asteroids_1.png", NULL);
            (*asteroids)[numAsteroids].size = 1.0f;

            (*asteroids)[numAsteroids].position.x = rand() % sfRenderWindow_getSize(window).x;
            (*asteroids)[numAsteroids].position.y = rand() % sfRenderWindow_getSize(window).y;

            (*asteroids)[numAsteroids].angle = (float)(rand() % 360);
            (*asteroids)[numAsteroids].speed = (float)((rand() % 5) + 1);
            //float angleInRadians = (*asteroids)[numAsteroids].angle * M_PI / 180.0f;
            (*asteroids)[numAsteroids].velocity.x = (*asteroids)[numAsteroids].speed * cos((*asteroids)[numAsteroids].angle);
            (*asteroids)[numAsteroids].velocity.y = (*asteroids)[numAsteroids].speed * sin((*asteroids)[numAsteroids].angle);


            printf("\n\nVELOCITY | x..%f        y..%f\n\n", (*asteroids)[numAsteroids].velocity.x, (*asteroids)[numAsteroids].velocity.y);


            
            sfSprite_setTexture((*asteroids)[numAsteroids].sprite, (*asteroids)[numAsteroids].texture, sfTrue);
            sfSprite_setOrigin((*asteroids)[numAsteroids].sprite, (sfVector2f) { 62 / 2, 46 / 2 });
            sfSprite_setPosition((*asteroids)[numAsteroids].sprite, (*asteroids)[numAsteroids].position);

            printf("\n\nSPAWN | Asteroid has spawned.\n\n");
            printf("\nNUMBER | Asteroid number %d.\n\n", numAsteroids);

            numAsteroids++;
        }
    }
    else {
        printf("ERREUR #0059 | Pointeur NULL to AsteroidsCreate.\n");
    }
}

void AsteroidsUpdate(sfRenderWindow* window, sfSprite* ship, Asteroid** asteroids) {
    
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

        /*if (asteroids[i].position.x < 0 || asteroids[i].position.x > windowSize.x) {
            asteroids[i].velocity.x = -asteroids[i].velocity.x;
        }

        if (asteroids[i].position.y < 0 || asteroids[i].position.y > windowSize.y) {
            asteroids[i].velocity.y = -asteroids[i].velocity.y;
        }*/


        if ((*asteroids)[i].position.x > windowSize.x)  
            (*asteroids)[i].position.x = 0;
        else if ((*asteroids)[i].position.x < 0)
            (*asteroids)[i].position.x = windowSize.x;

        if ((*asteroids)[i].position.y > windowSize.y)
            (*asteroids)[i].position.y = 0;
        else if ((*asteroids)[i].position.y < 0)
            (*asteroids)[i].position.y = windowSize.y;


        (*asteroids)[i].position.x += ((*asteroids)[i].velocity.x / 10) * dt;
        (*asteroids)[i].position.y += ((*asteroids)[i].velocity.y / 10) * dt;

        sfSprite_setPosition((*asteroids)[i].sprite, (*asteroids)[i].position);
    }
}

void AsteroidsDisplay(sfRenderWindow* window, Asteroid** asteroids) {
    for (int i = 0; i < numAsteroids; i++) {
        sfRenderWindow_drawSprite(window, (*asteroids)[i].sprite, NULL);
    } 
}

void AsteroidsDestroy(Asteroid** asteroids) {
    if (*asteroids != NULL) {
        for (int i = 0; i < numAsteroids; i++) {
            sfSprite_destroy((*asteroids)[i].sprite);
            sfTexture_destroy((*asteroids)[i].texture);
        }
        sfClock_destroy(respawnClock);
        free(*asteroids);
        *asteroids = NULL;
    }
    else {
        printf("ERREUR #0058 | Pointeur NULL to AsteroidsDestroy.\n");
    }
}
