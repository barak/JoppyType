#define MAX_TEXT_LENGTH 255

typedef struct Text_struct {

    /* Configuration */
    char *text;
    unsigned int scale;
    unsigned int x_position;
    unsigned int y_position;

    SDL_Texture *pre_index;
    SDL_Texture *post_index;
    SDL_Renderer *renderer;

    /* State */
    int index;

    /* Functions */
    void (*animate) (SDL_Rect *dest_rect);
    void (*render) (struct Text_struct *text);
    int  (*consume) (struct Text_struct *text, SDL_Keysym keysym);
    int  (*complete) (struct Text_struct *text);
} Text;

void Text_animate (SDL_Rect *dest_rect);
Text Text_new (SDL_Renderer *renderer, char *string);
