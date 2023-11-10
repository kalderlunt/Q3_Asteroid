// main.c
#include <stdio.h>
#include <stdlib.h>
#include "components/game.h"

int main() {
    Game game;
    GameInit(&game);
    GameLoop(&game);
    DestroyResources(&game);

    return 0;
}