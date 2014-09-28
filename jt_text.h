#define MAX_TEXT_LENGTH 255

typedef struct jt_text_struct {

    /* Configuration */
    char *text;
    uint32_t length;
    /* Size represents the amount of text that should fit across the
     * screen. A larger value for scale results in a smaller font size */
    uint32_t size;
    /* Position is stored as a value between 0.0 and 1.0.
     * 0.0 represents left-aligned text.
     * 0.5 represents centred text.
     * 1.0 represents right-alligned text. */
    float x_position;
    float y_position;

    SDL_Texture *typed_texture;
    SDL_Texture *untyped_texture;

    /* State */
    uint32_t index;
    uint32_t visible_index;

} jt_text;

void jt_text_animate (SDL_Rect *dest_rect);
int  jt_text_consume (jt_text *text, SDL_Keysym keysym);
void jt_text_render (jt_text *text, SDL_Renderer *renderer);
