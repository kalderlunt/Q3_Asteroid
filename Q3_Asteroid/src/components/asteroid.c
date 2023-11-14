#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SFML/Window.h"
#include "components/asteroid.h"
#include "components/deltaTime.h"

#define M_PI 3.14159265358979323846264338327950288

void AsteroidsInit(Asteroid** asteroids) {

    numAsteroids = 0;
    maxAsteroids = 20;

    *asteroids = malloc(maxAsteroids * sizeof(Asteroid));

    if (*asteroids == NULL) {
        printf("ERREUR #0050 | bullet initialization.\n");
        exit(EXIT_FAILURE);
    }

    (*asteroids)->texture = sfTexture_createFromFile("asset/Sprites/SpaceWar/asteroids_1.png", NULL);
    if (!(*asteroids)->texture) {
        printf("ERREUR #0053 | Unable to load texture for asteroids.\n");
    }

    for (int i = 0; i < maxAsteroids; i++) {
        (*asteroids)[i].texture = (*asteroids)->texture;
    }
}

void AsteroidsCreate(Asteroid* asteroids) {
    if (asteroids != NULL) {
        if (numAsteroids < maxAsteroids) {
            for (int i = 0; i < maxAsteroids; i++) {
                asteroids[i].sprite = sfSprite_create();
                
                if (asteroids[i].sprite != NULL) {
                    sfSprite_setTexture(asteroids[i].sprite, asteroids->texture, sfTrue);
                    sfSprite_setPosition(asteroids[i].sprite, asteroids->position);
                    asteroids[i].velocity = asteroids->velocity;

                    printf("ASTEROIDDDD\n");
                    printf("ASTEROIDDD\n");
                    printf("ASTEROIDD\n");
                    printf("ASTEROIDDD\n");
                    printf("ASTEROIDDDD\n");
                    sfSprite_move(asteroids[i].sprite, asteroids[i].velocity);
                    printf("Pouf vla\n");
                    numAsteroids ++;
                }
                else {
                    printf("ERREUR #0051 | Asteroid sprite creation.\n");
                }
            }
        }
        else {
            printf("ERREUR #00053 | Asteroid limit exceeded.\n");
        }
    }
    else {
        printf("ERREUR #0059 | Pointeur NULL to AsteroidsCreate.\n");
    }
}

void AsteroidsUpdate(sfRenderWindow* window, sfSprite* ship, Asteroid* asteroids) {
    

    sfVector2f shipPosition = sfSprite_getPosition(ship);

    sfVector2f dirAsteroid;
    dirAsteroid.x = asteroids->position.x - shipPosition.x;    // direction x
    dirAsteroid.y = asteroids->position.y - shipPosition.y;    // direction y 

    float magnitude = sqrt(dirAsteroid.x * dirAsteroid.x + dirAsteroid.y * dirAsteroid.y);      // norme

    if (magnitude > 0) {    // normalisation utile?
        (*asteroids).velocity.x = dirAsteroid.x / magnitude;
        (*asteroids).velocity.y = dirAsteroid.y / magnitude;
    }


    if (sfMouse_isButtonPressed(sfKeySpace)) {
        (*asteroids).position.x = rand() % sfRenderWindow_getSize(window).x;
        (*asteroids).position.y = rand() % sfRenderWindow_getSize(window).y;
        printf("%f  |  %f\n", asteroids->velocity.x, asteroids->velocity.y);

        AsteroidsCreate(asteroids);
    }
    
    for (int i = 0; i < numAsteroids; i++) {
        sfSprite_move(asteroids[i].sprite, asteroids[i].velocity);

        // Bounce off the window borders |/\| wraparound
        sfVector2u windowSize = sfRenderWindow_getSize(window);
        sfVector2f asteroidPos = sfSprite_getPosition(asteroids[i].sprite);

        if (asteroidPos.x < 0 || asteroidPos.x > windowSize.x) 
            asteroids[i].velocity.x = -asteroids[i].velocity.x;

        if (asteroidPos.y < 0 || asteroidPos.y > windowSize.y) 
            asteroids[i].velocity.y = -asteroids[i].velocity.y;
    }

    ///////////////////////////////////////////////////////////////printf("%d  ", numAsteroids);

    if (numAsteroids > maxAsteroids) {
        numAsteroids = maxAsteroids;
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
            // Destroy the sprite
            if (asteroids[i].sprite != NULL) {
                sfSprite_destroy(asteroids[i].sprite);
                asteroids[i].sprite = NULL;
            }

            // Destroy the texture
            if (asteroids[i].texture != NULL) {
                sfTexture_destroy(asteroids[i].texture);
                asteroids[i].texture = NULL;
            }
        }
    }
    else {
        printf("ERREUR #0058 | Pointeur NULL to AsteroidsDestroy.\n");
    }
    free(asteroids);
}
