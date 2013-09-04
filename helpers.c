#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
SDL_Surface *loadImage(char *filename) {

    SDL_Surface *initialImage;

    initialImage = IMG_Load(filename);

    if(initialImage == NULL) {
        fprintf(stderr, "Error loading image %s\n", filename);
        exit(EXIT_FAILURE);
    }

    return initialImage;
}

