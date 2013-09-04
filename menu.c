#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "timer.h"

#define FRAME_LIMIT 60

#include "shiftmap.h"
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
    char c = ' ';

    SDL_Surface *characters_bright = loadImage ("./Media/Terminus_bold_bright_green.png");
    SDL_Texture *characters_bright_texture = SDL_CreateTextureFromSurface (renderer, characters_bright);
    SDL_FreeSurface (characters_bright);

    SDL_Surface *characters_dim = loadImage ("./Media/Terminus_bold_dim_green.png");
    SDL_Texture *characters_dim_texture = SDL_CreateTextureFromSurface (renderer, characters_dim);
    SDL_FreeSurface (characters_dim);

    Text text;
    text.text = "Hello, World! Type to exit.";
    text.index = 0;
    text.pre_index = characters_dim_texture;
    text.post_index =  characters_bright_texture;


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
                        if (isascii(event.key.keysym.sym))
                        {
                            c = ( event.key.keysym.mod & KMOD_SHIFT
                                  ? shift_map[event.key.keysym.sym]
                                  : event.key.keysym.sym ) & 0x7F;

                            if (c == text.text[text.index])
                                text.index++;
                        }
                }
            }
        }

        if (text.index == strnlen (text.text, MAX_TEXT_LENGTH))
            return 0;

        /* Logic */

        /* Rendering */
        SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
        SDL_RenderClear (renderer);

        Text_render (renderer, &text);

        SDL_RenderPresent (renderer);

        /* Frame limiting */
        if (timer.time_passed (&timer) < (1000 / FRAME_LIMIT))
        {
            SDL_Delay (1000 / FRAME_LIMIT - timer.time_passed (&timer));
        }
    }

    SDL_FreeTexture (characters_bright_texture);
    SDL_FreeTexture (characters_dim_texture);

    return 0;
}

