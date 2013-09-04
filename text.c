#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"

#include "text.h"

void Text_render (SDL_Renderer *renderer, Text *text)
{
    int i = 0;
    SDL_Rect source_rect;
    SDL_Rect dest_rect;

    for (i = 0; text->text[i]; i++)
    {
        /* Calculate source */
        source_rect.x = 16 * (text->text[i] - ' ');
        source_rect.y = 0;
        source_rect.w =16;
        source_rect.h =32;
        
        /* Calculate destination */
        dest_rect.x = 120 + 64 * i;
        dest_rect.y = 120;
        dest_rect.w = 64;
        dest_rect.h = 128;

        if (i < text->index && text->pre_index)
            SDL_RenderCopy (renderer, text->pre_index, &source_rect, &dest_rect);
        else if (i >= text->index && text->post_index)
            SDL_RenderCopy (renderer, text->post_index, &source_rect, &dest_rect);
    }
        
}
