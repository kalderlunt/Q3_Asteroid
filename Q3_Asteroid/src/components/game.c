#include "components/game.h"

void GameInit(Game* game) {
    DeltaInit(&(game->deltaClock));
    WindowInit(&(game->window));
    BulletInit(&(game->bullets));
    AsteroidsInit(&(game->asteroids));
    PlayerInit(&(game->window), &(game->ship), &(game->shipTexture), &(game->shipRotation));
}

void GameUpdate(Game* game) {
    DeltaTime(game->deltaClock);
    BulletsUpdate(game->window, game->ship, game->bullets);
    AsteroidsUpdate(game->window, game->ship, &(game->asteroids));
    PlayerUpdate(game->window, game->ship, game->shipTexture, game->shipRotation);
}

void GameDisplay(Game* game) {
    sfRenderWindow_clear(game->window, sfTransparent);
    BulletsDisplay(game->window, game->bullets);
    AsteroidsDisplay(game->window, &(game->asteroids));
    PlayerDisplay(game->window, game->ship);
    WindowDisplay(game->window);
}
void DestroyResources(Game* game) {
    DeltaDestroy(&(game->deltaClock));
    BulletsDestroy(game->bullets);
    AsteroidsDestroy(&(game->asteroids));
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