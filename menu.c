#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

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

    TTF_Font *menu_font = TTF_OpenFont ("FreeMono.ttf", 20);
    if (menu_font == NULL)
    {
        fprintf (stderr, "Error: TTF_OpenFont failed.\n");
        exit (EXIT_FAILURE); /* TODO: A proper clean exit function */
    }

    SDL_Color text_colour = { 255, 255, 255, 0 };

    SDL_Surface *text_surface = TTF_RenderText_Blended (menu_font, "Sample text.", text_colour);
    if (text_surface == NULL)
    {
        fprintf (stderr, "Error: TTF_RenderText_Blended failed.\n");
        exit (EXIT_FAILURE); /* TODO: A proper clean exit function */
    }

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (text_texture == NULL)
    {
        fprintf (stderr, "Error: SDL_CreatTextureFromSurface failed.\n");
        exit (EXIT_FAILURE); /* TODO: A proper clean exit function */
    }

    SDL_Rect dest_rect;
    dest_rect.x = 320;
    dest_rect.y = 240;
    dest_rect.w = text_surface->w;
    dest_rect.h = text_surface->h;
    SDL_FreeSurface (text_surface);


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


        SDL_RenderCopy (renderer, text_texture, NULL, &dest_rect);

        SDL_RenderPresent (renderer);

        /* Frame limiting */
        if (timer.time_passed (&timer) < (1000 / FRAME_LIMIT))
        {
            SDL_Delay (1000 / FRAME_LIMIT - timer.time_passed (&timer));
        }
    }

    SDL_FreeTexture (text_texture);
    TTF_CloseFont (menu_font);

    return 0;
}

