#define MAX_TEXT_LENGTH 255

typedef struct Text_struct {
    char *text;
    int index;
    SDL_Texture *pre_index;
    SDL_Texture *post_index;
} Text;

void Text_render (SDL_Renderer *renderer, Text *text);
