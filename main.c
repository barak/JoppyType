#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#define FRAME_LIMIT 60

extern int main_menu (SDL_Renderer *renderer);

int main (int argc, char**argv)
{
    /* Initialize things */
    if (SDL_Init (SDL_INIT_EVERYTHING) == -1)
    {
        fprintf (stderr, "Error: SDL_Init failed.\n");
        return EXIT_FAILURE;
    }

    if (TTF_Init () == -1)
    {
        fprintf (stderr, "Error: TTF_Init failed.\n");
        return EXIT_FAILURE;
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_CreateWindowAndRenderer (0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
                                 &window, &renderer);

    if (window == NULL || renderer == NULL)
    {
        fprintf (stderr, "Error: SDL_CreateWindowAndRenderer failed.\n");
        return EXIT_FAILURE;
    }

    /* Clear the screen */
    SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
    SDL_RenderClear (renderer);
    SDL_RenderPresent (renderer);

    /* Enter the main menu */
    while (main_menu (renderer))
    {
        /* When there are multiple options, a switch statement could live in here... */
    }

    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    TTF_Quit ();
    SDL_Quit ();

    return EXIT_SUCCESS;
}
