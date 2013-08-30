#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"

#include "timer.h"

#define FRAME_LIMIT 60

/* main_menu
 *
 * The interactive main menu for the game.
 * Will return the next state to enter.
 */
int main_menu (SDL_Renderer *renderer)
{
    SDL_Event event;
    Timer timer = Timer_new ();

    for (;;)
    {
        timer.start(&timer);

        /* Process input */
        while (SDL_PollEvent (&event))
        {
            if (event.type == SDL_QUIT)
            {
                return 0;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        return 0;
                        break;
                }
            }
        }

        /* Logic */

        /* Rendering */
        SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
        SDL_RenderClear (renderer);
        SDL_RenderPresent (renderer);

        /* Frame limiting */
        if (timer.time_passed (&timer) < (1000 / FRAME_LIMIT))
        {
            SDL_Delay (1000 / FRAME_LIMIT - timer.time_passed (&timer));
        }
    }
    return 0;
}

