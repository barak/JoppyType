#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "SDL2/SDL.h"

#include "jt_shiftmap.h"
#include "jt_text.h"

/* Proportion of screen space that text covers */
#define JT_BORDER_X  0.05
#define JT_BORDER_Y 0.05

/* TODO:
 *  - It would be nice to allow the number of characters per line to
 *    vary and strectch to fill the screen. Using 'size' only as a
 *    suggestion.
 *  - Instead of lines just dissapearing instantly, perhaps a slow
 *    scroll as the line is typed, and the line fading away as it
 *    scrolls up. */
uint32_t min (uint32_t a, uint32_t b)
{
    return a > b ? b : a;
}

void jt_text_render (jt_text *text, SDL_Renderer *renderer)
{
    int i = 0;
    SDL_Rect source_rect;
    SDL_Rect dest_rect;
    uint32_t text_width;
    uint32_t text_height;
    uint32_t border_width;
    uint32_t border_height;
    uint32_t left_start;
    uint32_t right_shift;
    uint32_t top_start;
    uint32_t bottom_shift;
    uint32_t x_start;
    uint32_t y_start;
    uint32_t scale;

    int output_width;
    int output_height;

    /* Position in tile-space */
    uint32_t tile_x;
    uint32_t tile_y;
    uint32_t line_size;
    uint32_t remaining_space;
    uint32_t word_length;

    if (text->text == NULL)
        return;

    /* Calculate text destination area */
    SDL_GetRendererOutputSize (renderer, &output_width, &output_height);
    border_width = output_width * JT_BORDER_X;
    border_height = output_height * JT_BORDER_Y;

    /* Select font size */
    scale = (output_width - border_width * 2) / (text->size * 17 - 1);
    if (scale < 1)
        scale = 1;

    /* We have a goal size of text->size, but we can actually fit
     * line_size tiles at our best font size. */
    line_size = (output_width - border_width * 2) / (17 * scale);

    /* X Axis */
    text_width = 17 * scale * text->length - scale;
    left_start = border_width;
    right_shift = output_width - border_width * 2 - text_width;
    x_start = left_start + text->x_position * right_shift;

    /* Y Axis */
    text_height = 32 * scale;
    top_start = border_height;
    bottom_shift = output_height - border_height * 2 - text_height;
    y_start = top_start + text->y_position * bottom_shift;

    tile_x = 0;
    tile_y = 0;
    for (i = text->visible_index; text->text[i]; i++)
    {
        /* Select character from font */
        source_rect.x = 16 * (text->text[i] - ' ');
        source_rect.y =  0;
        source_rect.w = 16;
        source_rect.h = 32;

        /* Calculate tile destination */
        dest_rect.x = x_start + (16 + 1) * tile_x * scale;
        dest_rect.y = y_start + (32 + 8) * tile_y * scale;
        dest_rect.w = 16 * scale;
        dest_rect.h = 32 * scale;

        /* For now, animation is assumed. Perhaps make it optional in
         * the future */
        jt_text_animate (&dest_rect);

        if (i < text->index && text->typed_texture)
            SDL_RenderCopy (renderer, text->typed_texture, &source_rect, &dest_rect);
        else if (i >= text->index && text->untyped_texture)
            SDL_RenderCopy (renderer, text->untyped_texture, &source_rect, &dest_rect);

        /* Calculate next tile positon */
        if (text->text[i] == '\x7F')
        {
            tile_x = 0;
            tile_y++;
        }
        else if (text->text[i] == ' ')
        {
            /* Is there enough room for the next word? */
            remaining_space = line_size - tile_x - 1;
            word_length = min ( strchr (&text->text[i + 1], ' ') - &text->text[i + 1],
                                strlen (&text->text[i + 1]));
            if (word_length > remaining_space)
            {
                tile_x = 0;
                tile_y++;
            }
            else
            {
                tile_x++;
            }
        }
        else
        {
            tile_x++;
        }

        /* Have we managed to run out of line? */
        if (tile_x == line_size)
        {
            tile_x = 0;
            tile_y++;
        }

        /* Scroll the text */
        if (tile_x == 0 && tile_y == 1 && i < text->index)
        {
            text->visible_index = i + 1;
        }
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

    if (keysym.sym == SDLK_RETURN)
    {
        c = '\x7F';
    }
    else
    {
        /* Ignore any non-printable characters */
        if (!isprint (keysym.sym))
            return JT_TEXT_MISMATCH;

        /* Populate c with the keypress */
        if (keysym.mod & KMOD_SHIFT)
            c = shift_map[keysym.sym];
        else
            c = keysym.sym;
    }

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

