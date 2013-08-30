#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"

int main (int argc, char**argv)
{
    if (SDL_Init (SDL_INIT_EVERYTHING) == -1)
    {
        fprintf (stderr, "Error: SDL_Init failed.\n");
        return EXIT_FAILURE;
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_CreateWindowAndRenderer (640, 480, SDL_WINDOW_FULLSCREEN_DESKTOP,
                                 &window, &renderer);

    if (window == NULL || renderer == NULL)
    {
        fprintf (stderr, "Error: SDL_CreateWindowAndRenderer failed.\n");
        return EXIT_FAILURE;
    }

    SDL_SetRenderDrawColor (renderer, 255, 0, 0, 255); /* red */
    SDL_RenderClear (renderer);
    SDL_RenderPresent (renderer);


    SDL_Delay (5000);

    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    SDL_Quit ();

    return EXIT_SUCCESS;
}
