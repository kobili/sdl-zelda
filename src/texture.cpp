#include "texture.h"

#include "SDL_image.h"


Texture* load_texture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) {
        printf("Failed to load image surface: %s\n", IMG_GetError());
        return NULL;
    }

    int w = surface->w;
    int h = surface->h;

    SDL_Texture* _texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (_texture == NULL) {
        printf("Failed to load texture: %s\n", SDL_GetError());
        return NULL;
    }

    Texture* texture = (Texture*) malloc(sizeof(Texture));

    texture->texture = _texture;
    texture->w = w;
    texture->h = h;

    return texture;
}


void free_texture(Texture* texture) {
    SDL_DestroyTexture(texture->texture);
    free(texture);
}
