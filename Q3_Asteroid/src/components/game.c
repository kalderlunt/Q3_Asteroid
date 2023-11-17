#include "components/game.h"
#include "components/menu.h"


void GameInit(Game* game) {

    menuState = MENU;
    MenuInit();

    DeltaInit(&(game->deltaClock));
    WindowInit(&(game->window));
    BulletInit(&(game->bullets));
    AsteroidsInit(&(game->asteroids));
    PlayerInit(&(game->window), &(game->ship), &(game->shipTexture), &(game->shipRotation));
}

void GameUpdate(Game* game, sfEvent event) {
    switch (menuState)
    {
    case MENU:
        MenuUpdate(event, game->window);
        break;

    case GAME:
        DeltaTime(game->deltaClock);
        AsteroidsUpdate(game->window, game->ship, &(game->asteroids), &(game->bullets));
        BulletsUpdate(game->window, game->ship, game->bullets);
        PlayerUpdate(game->window, game->ship, game->shipTexture, game->shipRotation);
        break;

    case DIFFICULTY:
        break;

    case GAMEOVER:
        break;

    default:
        break;
    }
}

void GameDisplay(Game* game) {
    switch (menuState)
    {
    case MENU:
        MenuDisplay(game->window);
        break;

    case GAME:
        sfRenderWindow_clear(game->window, sfTransparent);
        AsteroidsDisplay(game->window, &(game->asteroids));
        BulletsDisplay(game->window, game->bullets);
        PlayerDisplay(game->window, game->ship);
        WindowDisplay(game->window);
        break;

    case DIFFICULTY:
        break;

    case GAMEOVER:
        break;

    default:
        break;
    }
}
void DestroyResources(Game* game) {
    switch (menuState)
    {
    case MENU:
        MenuDestroy();
        break;

    case GAME:
        DeltaDestroy(&(game->deltaClock));
        BulletsDestroy(game->bullets);
        AsteroidsDestroy(&(game->asteroids));
        PlayerDestroy(game->ship, game->shipTexture);
        WindowDestroy(game->window);
        break;

    case DIFFICULTY:
        break;

    case GAMEOVER:
        break;

    default:
        break;
    }
}

void GameLoop(Game* game) {
    while (sfRenderWindow_isOpen(game->window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(game->window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(game->window);
            }
        }

        GameUpdate(game, event);
        GameDisplay(game);
    }
}