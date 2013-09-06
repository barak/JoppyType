#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "SDL2/SDL.h"

#include "shiftmap.h"
#include "text.h"

void Text_render (Text *text)
{
    int i = 0;
    SDL_Rect source_rect;
    SDL_Rect dest_rect;

    for (i = 0; text->text[i]; i++)
    {
        /* Calculate source */
        source_rect.x = 16 * (text->text[i] - ' ');
        source_rect.y =  0;
        source_rect.w = 16;
        source_rect.h = 32;

        /* Calculate destination */
        dest_rect.x = text->x_position + (64 + 4) * i;
        dest_rect.y = text->y_position;
        dest_rect.w =  64;
        dest_rect.h = 128;

        if (text->animate)
            text->animate(&dest_rect);

        if (i < text->index && text->pre_index)
            SDL_RenderCopy (text->renderer, text->pre_index, &source_rect, &dest_rect);
        else if (i >= text->index && text->post_index)
            SDL_RenderCopy (text->renderer, text->post_index, &source_rect, &dest_rect);
    }
}

int Text_complete (Text *text)
{
    if (text->index >= strnlen (text->text, MAX_TEXT_LENGTH))
    {
        return 1;
    }
    return 0;
}

/* Consume a keypress.
 * Returns: 0 - No change in state.
 *          1 - A character was accepted.
 *          2 - The entire text has been accepted.
 */
int Text_consume (Text *text, SDL_Keysym keysym)
{
    char c = '\0';

    if (isascii(keysym.sym))
    {
        c = (   keysym.mod & KMOD_SHIFT
                ? shift_map[keysym.sym]
                : keysym.sym
            ) & 0x7F;

        if (c == text->text[text->index])
        {
            text->index++;
            if (text->complete(text))
            {
                return 2;
            }
            return 1;
        }
    }
    return 0;
}

void Text_animate (SDL_Rect *dest_rect)
{
    dest_rect->y += 0.025 * dest_rect->h * sin (SDL_GetTicks() / 200.0 + dest_rect->x + dest_rect->y);
}

Text Text_new (SDL_Renderer *renderer, char *string)
{
    Text text = { string, 0, 0, NULL, NULL, renderer,
                  0,
                  NULL, &Text_render, &Text_consume, &Text_complete
                };
    return text;
}
