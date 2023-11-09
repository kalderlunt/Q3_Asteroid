#ifndef DELTATIME_H
#define DELTATIME_H

#include <SFML/Graphics.h>

int dt;

void DeltaInit(sfClock** deltaClock);

void DeltaTime(sfClock* deltaClock);

void DeltaDestroy(sfClock* deltaClock);

#endif /*DELTATIME_H*/