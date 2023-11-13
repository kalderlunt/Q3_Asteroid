#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.h>

void WindowInit(sfRenderWindow** window);

void WindowDisplay(sfRenderWindow* window);

void WindowDestroy(sfRenderWindow* window);

#endif /*WINDOW_H*/