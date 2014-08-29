#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "timer.h"

#define FRAME_LIMIT 60

#include "helpers.h"
#include "text.h"

int run_game (SDL_Renderer *renderer)
{
    SDL_Event event;
    Timer timer = Timer_new ();
    char score_string[MAX_TEXT_LENGTH] = {'\0'};
    int score_int = 0;

    /* Load textures */
    SDL_Texture *background_texture      = loadTexture (renderer, "./Media/Greenmaze.png");
    SDL_Texture *character_tiles_texture = loadTexture (renderer,"./Media/Terminus_bold_tiles_b.png");
    SDL_Texture *characters_dim_texture  = loadTexture (renderer,"./Media/Terminus_bold_tiles_b_trans.png");

    Text score = Text_new (renderer, score_string);
    score.post_index =  character_tiles_texture;
    score.scale = 2;
    score.x_position = 10;
    score.y_position = 10;

    Text text = Text_new (renderer, "This is gameplay.");
    text.scale = 4;
    text.pre_index  =  characters_dim_texture;
    text.post_index =  character_tiles_texture;
    text.x_position = 320;
    text.y_position = 600;
    text.animate = &Text_animate;


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
                        if (text.consume (&text, event.key.keysym))
                            score_int++;
                }
            }
        }

        /* Logic */
        if (text.complete (&text))
            return 0;


        /* Rendering */
        SDL_SetRenderDrawColor (renderer, 0x00, 0x80, 0x00, 0xFF);
        SDL_RenderClear (renderer);

        SDL_RenderCopy (renderer, background_texture, NULL, NULL);

        text.render (&text);

        snprintf (score_string, MAX_TEXT_LENGTH, "Score: %d.\n", score_int);
        score.render (&score);

        SDL_RenderPresent (renderer);

        /* Frame limiting */
        if (timer.time_passed (&timer) < (1000 / FRAME_LIMIT))
        {
            SDL_Delay (1000 / FRAME_LIMIT - timer.time_passed (&timer));
        }
    }

    SDL_FreeTexture (character_tiles_texture);
    SDL_FreeTexture (characters_dim_texture);
    SDL_FreeTexture (background_texture);

    return 0;
}

