#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SFML/Window.h"
#include "components/asteroid.h"

#define M_PI 3.14159265358979323846264338327950288

void AsteroidsInit(Asteroid** asteroids) {

    numAsteroids = 0;
    maxAsteroids = memoryMaxAsteroids;
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

int CheckCollision(Bullet** bullets, Asteroid** asteroids) {

    sfVector2f distBetween;
    float dist;
    float distCollision = 5.0f;
    
    sfVector2f shipPosition = sfSprite_getPosition(*bullets);

    for (int i = 0; i < numBullets; i++) {
        for (int j = 0; j < numAsteroids; j++) {
            /*
            sfFloatRect bulletBounds = sfSprite_getGlobalBounds((*bullets)[i].sprite);
            sfFloatRect asteroidBounds = sfSprite_getGlobalBounds((*asteroids)[j].sprite);

            if (sfFloatRect_intersects(&bulletBounds, &asteroidBounds, NULL)) {
                // Collision détectée entre la balle i et l'astéroïde j
                // marquer la balle et l'astéroïde comme "détruits"
                // bullets[i] et asteroids[j]
                // Ou fonction de destruction.
                return j; // Collision detected
            }
            */
            
            distBetween.x = (*asteroids)[i].position.x - shipPosition.x;
            distBetween.y = (*asteroids)[i].position.y - shipPosition.y;

            dist = distBetween.x + distBetween.y;
            
            if (dist <= distCollision) {
                printf("CHECCKKK COLLLISION CHECK !");
                return 1;
            }
        }
    }



    return -1; // any collision detect
}

void CreateSmallAsteroids(sfVector2f position, sfVector2f velocity, Asteroid** asteroids) {
    if (*asteroids != NULL) {
        // Création des deux nouveaux astéroïdes plus petits
        (*asteroids)[numAsteroids].sprite = sfSprite_create();
        (*asteroids)[numAsteroids].texture = sfTexture_createFromFile("asset/Sprites/SpaceWar/small_asteroid.png", NULL);
        // Configuration premier astéroïde
        // position, vitesse, taille, etc.
        // ...

        // Incrémentez numAsteroids pour le premier nouvel astéroïde créé
        numAsteroids++;

        // Faites de même pour le deuxième nouvel astéroïde plus petit
        // ...
    }
}

void AsteroidRemove(int index, Asteroid** asteroids) {
    if (*asteroids != NULL && numAsteroids > 0 && index >= 0 && index < numAsteroids) {
        // Déplacez le dernier astéroïde dans la liste à l'emplacement de l'astéroïde supprimé
        (*asteroids)[index] = (*asteroids)[numAsteroids - 1];
        numAsteroids--;
    }
}

void HandleCollisions(Bullet** bullets, Asteroid** asteroids) {
    int asteroidHit = CheckCollision(bullets, asteroids);

    if (asteroidHit) {
        sfVector2f asteroidPosition = (*asteroids)[asteroidHit].position;
        sfVector2f asteroidVelocity = (*asteroids)[asteroidHit].velocity;

        CreateSmallAsteroids(asteroidPosition, asteroidVelocity, asteroids);

        AsteroidRemove(asteroidHit, asteroids);
    }
}

void AsteroidsUpdate(sfRenderWindow* window, sfSprite* ship, Asteroid** asteroids, Bullet** bullets) {
    
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


        //HandleCollisions(*bullets, *asteroids);


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
