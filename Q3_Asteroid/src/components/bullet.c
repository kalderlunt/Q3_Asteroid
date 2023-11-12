#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "components/bullet.h"
#include "components/deltaTime.h"

#define M_PI 3.14159265358979323846264338327950288



void BulletInit(Bullet** bullets, int* numBullets, int* maxBullets, float* bulletRotation) {
    *numBullets = 0;
    *maxBullets = 10;


    // Allocation de mémoire pour le tableau de balles
    *bullets = malloc(*maxBullets * sizeof(Bullet));
    
    if (*bullets == NULL) {
        printf("ERREUR #0040 | bullet initialization.\n");
        exit(EXIT_FAILURE);
    }




    sfTexture* texture = sfTexture_createFromFile("asset/Sprites/SpaceWar/cannon.png", NULL);
    if (texture == NULL) {
        // Gestion de l'erreur de chargement de la texture
        printf("ERREUR #0043 | Impossible de charger la texture pour les balles.\n");
        // Gérer l'erreur, par exemple, retourner ou quitter la fonction.
    }

    // Initialisez chaque balle avec la texture chargée
    for (int i = 0; i < *maxBullets; i++) {
        (*bullets)[i].texture = texture;
    }



}


void BulletCreate(Bullet* bullets, int* numBullets, int maxBullets, sfTexture* texture, sfVector2f position, sfVector2f velocity, float bulletRotation) {

    if (bullets != NULL && numBullets != NULL && texture != NULL) {
        if (*numBullets < maxBullets) {
            bullets[*numBullets].sprite = sfSprite_create();

            // Vérifier si la création du sprite a réussi
            if (bullets[*numBullets].sprite != NULL) {
                sfSprite_setTexture(bullets[*numBullets].sprite, texture, sfTrue);
                sfSprite_setPosition(bullets[*numBullets].sprite, position);
                bullets[*numBullets].velocity = velocity;

                //sfSprite_setOrigin(bullets, (sfVector2f) { 10, 9 });
                //sfSprite_setRotation(bullets, bulletRotation);
                sfSprite_setOrigin(bullets[*numBullets].sprite, (sfVector2f) { 10, 9 });
                sfSprite_setRotation(bullets[*numBullets].sprite, bulletRotation);
                
                sfSprite_move(bullets[*numBullets].sprite, bullets[*numBullets].velocity);
                printf("PEW  |  PEW\n");
                (*numBullets)++;
                
            }
            else {
                // Gestion de l'échec de création du sprite
                printf("ERREUR #0041 | Bullet sprite creation.\n");
            }
        }
        else {
            // Gestion de dépassement de la limite des balles
            printf("ERREUR | Depassement de la limite des balles.\n");
        }
    }
    else {
        // Gestion de cas où des pointeurs sont NULL
        printf("ERREUR | Pointeur NULL passé à BulletCreate.\n");
    }
}





void BulletsUpdate(sfRenderWindow* window, sfSprite* ship, Bullet* bullets, int* numBullets, int maxBullets, float bulletRotation) {
    // POSITION
    sfVector2i mousePosition = sfMouse_getPositionRenderWindow(window);
    sfVector2f shipPosition = sfSprite_getPosition(ship);

    sfVector2f dir;
    dir.x = mousePosition.x - shipPosition.x;    // direction x
    dir.y = mousePosition.y - shipPosition.y;    // direction y 

    float magnitude = sqrt(dir.x * dir.x + dir.y * dir.y);      // norme

    if (magnitude > 0) {    // normalisation utile?
        dir.x /= magnitude;
        dir.y /= magnitude;
    }


    bulletRotation = atan2f(dir.y, dir.x) * 180.0f / M_PI;

    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        sfVector2f bulletPosition = sfSprite_getPosition(ship);
        sfVector2f bulletVelocity = { dir.x, dir.y };
        printf("%f  |  %f\n", bulletVelocity.x, bulletVelocity.y);

        BulletCreate(bullets, numBullets, maxBullets, bullets->texture, bulletPosition, bulletVelocity, bulletRotation);
    }

    for (int i = 0; i < *numBullets; i++) {
        sfSprite_move(bullets[i].sprite, bullets[i].velocity);
    }


    if (*numBullets > maxBullets) {
        *numBullets = maxBullets;
    }
}


void BulletsDisplay(sfRenderWindow* window, Bullet* bullets, int numBullets) {
    for (int i = 0; i < numBullets; i++) {
        sfRenderWindow_drawSprite(window, bullets[i].sprite, NULL);
    }
}


void BulletsDestroy(Bullet* bullets, int numBullets, int maxBullets) {
    if (bullets != NULL) {
        for (int i = 0; i < numBullets; i++) {
            if (bullets[i].sprite != NULL) {
                sfSprite_destroy(bullets[i].sprite);
                bullets[i].sprite = NULL;
            }
            // Libérez la texture de chaque balle
            if (bullets[i].texture != NULL) {
                sfTexture_destroy(bullets[i].texture);
                bullets[i].texture = NULL;
            }
        }
    }
    free(bullets);
}