#define MAX_TEXT_LENGTH 255

typedef struct jt_text_struct {

    /* Configuration */
    char *text;
    uint32_t length;
    unsigned int scale;
    unsigned int x_position;
    unsigned int y_position;

    SDL_Texture *typed_texture;
    SDL_Texture *untyped_texture;

    /* State */
    int index;

} jt_text;

void jt_text_animate (SDL_Rect *dest_rect);
int  jt_text_consume (jt_text *text, SDL_Keysym keysym);
void jt_text_render (jt_text *text, SDL_Renderer *renderer);
