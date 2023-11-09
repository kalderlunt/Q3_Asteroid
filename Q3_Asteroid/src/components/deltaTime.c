#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "components/deltaTime.h"


void DeltaInit(sfClock** deltaClock) {
    *deltaClock = sfClock_create();
}

void DeltaTime(sfClock* deltaClock) {
    sfTime dtime = sfClock_getElapsedTime(deltaClock);
    dt = sfTime_asMilliseconds(dtime) * 0.001;
    sfClock_restart(deltaClock);
}

void DeltaDestroy(sfClock* deltaClock) {
    sfClock_destroy(deltaClock);
}