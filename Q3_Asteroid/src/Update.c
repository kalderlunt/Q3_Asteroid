#include <stdio.h>
#include <conio.h>
#include "../include/Update.h"

// Update du jeu

//void Update(int x, int y, int tailX[], int tailY[], int nbTail, int widthWindow, int heightWindow, int fruitX, int fruitY, int score, int speedSnake, bool gameover, const char charGameOver)

void Setup() {
    gameover = false;                   //charGameOver = 'x';

    widthWindow = 50;           heightWindow = 15;
    x = 9;        y = 9;
    
    size = 20;
    winWidth = 500;             winHeight = 400;

    dir = RIGHT;

    fruitX = rand() % winWidth %size ;        fruitY = rand() % winHeight;

    score = 0;
    speedSnake = 120;

    nbTail = 2;
    for (int i = 0; i <= nbTail; i++) {
        tailX[i] = x - i; // Initialise les positions des queues supplémentaires
        tailY[i] = y;
    }
}


void Update(char charGameOver, sfRenderWindow* window, sfRectangleShape* snake, sfCircleShape* fruit) {
    MovementTail();
    MovementPlayer(window, snake);

    Collision(charGameOver);
}


void MovementTail() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nbTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
}

void Input() {
    prevDir = dir;
    if (sfKeyboard_isKeyPressed(sfKeyW) && prevDir != DOWN)
        dir = UP;
    else if (sfKeyboard_isKeyPressed(sfKeyA) && prevDir != RIGHT)
        dir = LEFT;
    else if (sfKeyboard_isKeyPressed(sfKeyD) && prevDir != LEFT)
        dir = RIGHT;
    else if (sfKeyboard_isKeyPressed(sfKeyS) && prevDir != UP)
        dir = DOWN;
    else if (sfKeyboard_isKeyPressed(sfKeySpace)) 
        gameover = true;
}

void MovementPlayer(sfRenderWindow* window, sfRectangleShape* snake) {

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    sfRectangleShape_setPosition(snake, (sfVector2f) { x* size, y* size });
}

void Collision(char charGameOver) {
    if (x >= winWidth / size-1 || x < 0)
        gameover = true;
    if (y >= winHeight /size -1 || y < 0)
        gameover = true; 

    //if (x >= winWidth/size) x = -1; else if (x < 0) x = winWidth/size;
    //if (y >= winHeight) y = 0; else if (y < 0) y = winHeight - 1;

    /*for (int i = 0; i < nbTail; i++) // Vérifie si le serpent se mord la queue
        if (tailX[i] == x && tailY[i] == y) 
            gameover = true;*/

    // FRUITIIITUIS
    EatFruit();

}

void EatFruit() {
    if (x == fruitX && y == fruitY) { // Le serpent mange un fruit
        fruitX = rand() % winWidth;
        fruitY = rand() % winHeight;
        score += 10;
        nbTail += 2;
        if (speedSnake > 0)
            speedSnake -= 3;
        else 
            speedSnake = 0;
    }

    //CollisionSpawnFruit();
}
void CollisionSpawnFruit() {
    for (int i = 0; i < nbTail; i++) // Vérifie si le serpent se mord la queue
        if (tailX[i] == fruitX && tailY[i] == fruitY) {
            fruitX = rand() % widthWindow;
            fruitY = rand() % heightWindow;
        }
}





void Draw(char charGameOver, sfRenderWindow* window, sfRectangleShape* snake, sfCircleShape* fruit) {
    //system("cls"); // Clear Screen Console

    //DrawGame();
    DrawSnake(window, snake);
    DrawFruit(window, fruit);

    //DrawScore();

    //DrawDeath(charGameOver);
    
    // WINDOW DISPLAY
    sfRenderWindow_display(window);
}

void DrawGame() {
    // Dessine le cadre supérieur
    for (int i = 0; i < widthWindow + 2; i++)
        printf("#");
    printf("\n");

    // Dessine le jeu (serpent, fruit et espace vide)
    for (int i = 0; i < heightWindow; i++) {
        for (int j = 0; j < widthWindow; j++) {
            if (j == 0)
                printf("#");
            if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else {
                bool print = false;
                for (int k = 0; k < nbTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        print = true;
                    }
                }
                if (!print)
                    printf(" ");
            }
            if (j == widthWindow - 1)
                printf("#");
        }
        printf("\n");
    }

    // Cadre inférieur
    for (int i = 0; i < widthWindow + 2; i++)
        printf("#");
    printf("\n");
}

void DrawSnake(sfRenderWindow* window, sfRectangleShape* snake) {
    sfRenderWindow_drawRectangleShape(window, snake, NULL);
}

void DrawFruit(sfRenderWindow* window, sfCircleShape* fruit) {
    sfRenderWindow_drawCircleShape(window, fruit, NULL);
}

void DrawScore() {
    // Affichage score et vitesse | actuelle du serpent
    printf("Score: %d\n", score);
    //printf("Vitesse: %d\n", speedSnake);
}

void DrawDeath(char charGameOver) {
    // Mort
    if (gameover == true)
    {
        printf("\n                     GAME OVER !\n");
        printf("                Press %c To Restart\n\n\n", charGameOver);
    }
}