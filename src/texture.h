#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"

struct Texture {
    SDL_Texture* texture;
    int w;
    int h;
};

Texture* load_texture(SDL_Renderer* renderer, const char* path);
void free_texture(Texture* texture);

#endif
