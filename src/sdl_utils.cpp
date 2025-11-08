#include "sdl_utils.h"

#include "SDL.h"
#include "SDL_image.h"


int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags)) {
        printf("Failed to initialize SDL_Image: %s\n", IMG_GetError());
        return -1;
    }

    return 0;
}


void teardown_sdl() {
    IMG_Quit();
    SDL_Quit();
}
