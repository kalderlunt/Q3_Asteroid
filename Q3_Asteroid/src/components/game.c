#include "components/game.h"
#include "components/window.h"
#include "components/player.h"
#include "components/deltaTime.h"
#include "components/bullet.h"

void GameInit(Game* game) {
    DeltaInit(&(game->deltaClock));
    WindowInit(&(game->window));
    BulletInit(&(game->bullets), &(game->numBullets), &(game->maxBullets));
    PlayerInit(&(game->window), &(game->ship), &(game->shipTexture), &(game->shipRotation));
}

void GameUpdate(Game* game) {
    DeltaTime(game->deltaClock);
    BulletsUpdate(game->window, game->ship, game->bullets, &(game->numBullets), game->maxBullets);
    PlayerUpdate(game->window, game->ship, game->shipTexture, game->shipRotation);
}

void GameDisplay(Game* game) {
    sfRenderWindow_clear(game->window, sfTransparent);
    PlayerDisplay(game->window, game->ship);
    BulletsDisplay(game->window, game->bullets, game->numBullets);
    WindowDisplay(game->window);
}
void DestroyResources(Game* game) {
    DeltaDestroy(&(game->deltaClock));
    BulletsDestroy(game->bullets, game->numBullets, game->maxBullets);
    PlayerDestroy(game->ship, game->shipTexture);
    WindowDestroy(game->window);
}

void GameLoop(Game* game) {
    while (sfRenderWindow_isOpen(game->window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(game->window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(game->window);
            }
        }

        GameUpdate(game);
        GameDisplay(game);
    }
}