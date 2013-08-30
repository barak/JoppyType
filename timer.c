#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"

#include "timer.h"

void Timer_start (Timer *t)
{
    t->start_time = SDL_GetTicks ();
}

unsigned int Timer_time_passed (Timer *t)
{
    return SDL_GetTicks () - t->start_time;
}

Timer Timer_new ()
{
    Timer t = { 0, &Timer_start, &Timer_time_passed };
    return t;
}

