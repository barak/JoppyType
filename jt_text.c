#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "SDL2/SDL.h"

#include "jt_shiftmap.h"
#include "jt_text.h"

void jt_text_render (jt_text *text, SDL_Renderer *renderer)
{
    int i = 0;
    SDL_Rect source_rect;
    SDL_Rect dest_rect;

    if (text->text == NULL)
        return;

    for (i = 0; text->text[i]; i++)
    {
        /* Select character from font */
        source_rect.x = 16 * (text->text[i] - ' ');
        source_rect.y =  0;
        source_rect.w = 16;
        source_rect.h = 32;

        /* Calculate destination rectangle */
        dest_rect.x = text->x_position + (16 + 1) * i * text->scale;
        dest_rect.y = text->y_position;
        dest_rect.w = 16 * text->scale;
        dest_rect.h = 32 * text->scale;;

        /* For now, animation is assumed. Perhaps make it optional in
         * the future */
        jt_text_animate (&dest_rect);

        if (i < text->index && text->typed_texture)
            SDL_RenderCopy (renderer, text->typed_texture, &source_rect, &dest_rect);
        else if (i >= text->index && text->untyped_texture)
            SDL_RenderCopy (renderer, text->untyped_texture, &source_rect, &dest_rect);
    }
}

/* Consume a keypress */
#define JT_TEXT_MISMATCH 0
#define JT_TEXT_MATCH    1
#define JT_TEXT_COMPLETE 2
int jt_text_consume (jt_text *text, SDL_Keysym keysym)
{
    char c = '\0';

    /* Ignore any non-ascii characters */
    if (keysym.sym >= 0x80)
       return JT_TEXT_MISMATCH;

    /* Ignore any non-printable characters */
    if (!isprint (keysym.sym))
        return JT_TEXT_MISMATCH;

    /* Populate c with the keypress */
    if (keysym.mod & KMOD_SHIFT)
        c = shift_map[keysym.sym];
    else
        c = keysym.sym;

    if (c == text->text[text->index])
    {
        text->index++;
        if (text->index == text->length)
            return JT_TEXT_COMPLETE;
        else
            return JT_TEXT_MATCH;
    }
    
    return JT_TEXT_MISMATCH;
}

void jt_text_animate (SDL_Rect *dest_rect)
{
    dest_rect->y += 0.025 * dest_rect->h * sin (SDL_GetTicks() / 200.0 + dest_rect->x + dest_rect->y);
}

