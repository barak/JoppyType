#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "timer.h"

#define FRAME_LIMIT 60

#include "helpers.h"
#include "text.h"

/* main_menu
 *
 * The interactive main menu for the game.
 * Will return the next state to enter.
 */
int main_menu (SDL_Renderer *renderer)
{
    SDL_Event event;
    Timer timer = Timer_new ();

    SDL_Surface *background_surface = loadImage ("./Media/Greenmaze.png");
    SDL_Texture *background_texture = SDL_CreateTextureFromSurface (renderer, background_surface);
    SDL_FreeSurface (background_surface);

    SDL_Surface *character_tiles_surface = loadImage ("./Media/Terminus_bold_tiles_b.png");
    SDL_Texture *character_tiles_texture = SDL_CreateTextureFromSurface (renderer, character_tiles_surface);
    SDL_FreeSurface (character_tiles_surface);

    SDL_Surface *characters_dim = loadImage ("./Media/Terminus_bold_tiles_b_trans.png");
    SDL_Texture *characters_dim_texture = SDL_CreateTextureFromSurface (renderer, characters_dim);
    SDL_FreeSurface (characters_dim);

    Text title = Text_new (renderer, "Welcome to JoppyType!");
    title.post_index =  character_tiles_texture;
    title.x_position = 120;
    title.y_position = 120;
    title.animate = &Text_animate;

    Text start = Text_new (renderer, "Start");
    start.pre_index  =  characters_dim_texture;
    start.post_index =  character_tiles_texture;
    start.x_position = 320;
    start.y_position = 440;
    start.animate = &Text_animate;

    Text exit = Text_new (renderer, "Exit");
    exit.pre_index  =  characters_dim_texture;
    exit.post_index =  character_tiles_texture;
    exit.x_position = 320;
    exit.y_position = 600;
    exit.animate = &Text_animate;


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
                    default:
                        start.consume (&start, event.key.keysym);
                        exit.consume (&exit, event.key.keysym);
                }
            }
        }

        /* Logic */
        if (start.complete (&start))
            return 1;
        if (exit.complete (&exit))
            return 0;


        /* Rendering */
        SDL_SetRenderDrawColor (renderer, 0x00, 0x80, 0x00, 0xFF);
        SDL_RenderClear (renderer);

        SDL_RenderCopy (renderer, background_texture, NULL, NULL);

        title.render (&title);
        start.render (&start);
        exit.render (&exit);

        SDL_RenderPresent (renderer);

        /* Frame limiting */
        if (timer.time_passed (&timer) < (1000 / FRAME_LIMIT))
        {
            SDL_Delay (1000 / FRAME_LIMIT - timer.time_passed (&timer));
        }
    }

    SDL_FreeTexture (character_tiles_texture);
    SDL_FreeTexture (characters_dim_texture);
    SDL_FreeTexture (background_surface);

    return 0;
}

