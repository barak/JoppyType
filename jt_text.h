#define MAX_TEXT_LENGTH 255

typedef struct jt_text_struct {

    /* Configuration */
    char *text;
    uint32_t length;
    /* TODO: Change definition of scale to represent the number of
     * characters that we want to fit across the screen */
    uint32_t scale;
    /* Position is stored as a value between 0.0 and 1.0.
     * 0.0 represents left-aligned text.
     * 0.5 represents centred text.
     * 1.0 represents right-alligned text. */
    float x_position;
    float y_position;

    SDL_Texture *typed_texture;
    SDL_Texture *untyped_texture;

    /* State */
    int index;

} jt_text;

void jt_text_animate (SDL_Rect *dest_rect);
int  jt_text_consume (jt_text *text, SDL_Keysym keysym);
void jt_text_render (jt_text *text, SDL_Renderer *renderer);
