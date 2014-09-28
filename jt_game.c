#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "jt_helpers.h"
#include "jt_text.h"

#define FRAME_LIMIT 60
/* TODO: The score is shown on the left.. How about WPM on the right? */
/* Once the basics of text handling are complete, this should be
 * replaced with the ability to load text from a file. */
/* For now, 0x7F can represent \n, to avoid changing the font code and format */
char *initial_text = "This is a sample piece of text. Type type type go the "
                     "fingers on the keyboard. The keyboard makes a satisfying "
                     "clack noise as the keys bottom out.\x7F"
                     "After some more of this code is written, I think I might "
                     "relax with a bag of chips and watch the telly for a bit.\x7F";

int jt_run_game (SDL_Renderer *renderer)
{
    SDL_Event event;
    uint32_t frame_start;
    uint32_t frame_stop;
    char score_string[MAX_TEXT_LENGTH] = {'\0'};
    int score_int = 0;

    /* Load textures */
    SDL_Texture *background_texture      = loadTexture (renderer, "./Media/Greenmaze.png");
    SDL_Texture *character_tiles_texture = loadTexture (renderer,"./Media/Terminus_bold_tiles_b.png");
    SDL_Texture *characters_dim_texture  = loadTexture (renderer,"./Media/Terminus_bold_tiles_b_trans.png");

    jt_text score = { score_string, 0, 40,
                      0.0, 0.0,
                      character_tiles_texture, character_tiles_texture,
                      0, 0 };

    jt_text text = { initial_text, strlen (initial_text), 30,
                      0.0, 0.2,
                      characters_dim_texture, character_tiles_texture,
                      0, 0 };

    for (;;)
    {
        frame_start = SDL_GetTicks ();

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
                        if (jt_text_consume (&text, event.key.keysym))
                            score_int++;
                        break;
                }
            }
        }

        /* Logic */
        if (text.index == text.length)
            return 0;


        /* Rendering */
        SDL_SetRenderDrawColor (renderer, 0x00, 0x80, 0x00, 0xFF);
        SDL_RenderClear (renderer);

        SDL_RenderCopy (renderer, background_texture, NULL, NULL);

        jt_text_render (&text, renderer);

        snprintf (score_string, MAX_TEXT_LENGTH, "Score: %d.\n", score_int);
        jt_text_render (&score, renderer);

        SDL_RenderPresent (renderer);

        /* Frame limiting */
        frame_stop = SDL_GetTicks ();
        if ((frame_stop - frame_start) < (1000 / FRAME_LIMIT))
        {
            SDL_Delay (1000 / FRAME_LIMIT - (frame_stop - frame_start));
        }
    }

    SDL_DestroyTexture (character_tiles_texture);
    SDL_DestroyTexture (characters_dim_texture);
    SDL_DestroyTexture (background_texture);

    return 0;
}

