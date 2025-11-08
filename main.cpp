#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_image.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


struct Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
};


Window* create_window() {
    SDL_Window* sdl_window = SDL_CreateWindow(
        "Zeldeep",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (sdl_window == NULL) {
        printf("failed to create window: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Failed to get renderer: %s\n", SDL_GetError());

        SDL_DestroyWindow(sdl_window);
        return NULL;
    }

    Window* window = (Window*) malloc(sizeof(Window));

    window->window = sdl_window;
    window->renderer = renderer;

    return window;
}


struct Texture {
    SDL_Texture* texture;
    int w;
    int h;
};


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


struct SpriteSheet {
    Texture* texture;
    int rows;
    int cols;
    int sprite_width_px;
    int sprite_height_px;
};


SpriteSheet create_sprite_sheet(Texture* texture, int sprite_width_px, int sprite_height_px) {
    SpriteSheet sprite_sheet;
    sprite_sheet.texture = texture;

    sprite_sheet.sprite_width_px = sprite_width_px;
    sprite_sheet.sprite_height_px = sprite_height_px;

    sprite_sheet.cols = texture->w / sprite_width_px;
    sprite_sheet.rows = texture->h / sprite_height_px;

    return sprite_sheet;
}

SDL_Rect get_sprite(SpriteSheet sprite_sheet, int x, int y) {
    SDL_Rect src;
    src.w = sprite_sheet.sprite_width_px;
    src.h = sprite_sheet.sprite_height_px;

    src.x = x * sprite_sheet.sprite_width_px;
    src.y = y * sprite_sheet.sprite_height_px;

    return src;
}


int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags)) {
        printf("Failed to initialize SDL_Image: %s\n", IMG_GetError());
        return -1;
    }

    Window* window = create_window();
    if (window == NULL) {
        printf("Failed to create window. Exiting...\n");
        return -1;
    }
    SDL_Renderer* renderer = window->renderer;

    Texture* texture = load_texture(renderer, "resources/link_walk_sprite.png");
    if (texture == NULL) {
        printf("failed to load texture. Exiting...\n");
        return -1;
    }

    SpriteSheet sprite_sheet = create_sprite_sheet(texture, 16, 16);
    texture = NULL;

    SDL_Event e;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        SDL_Rect src = get_sprite(sprite_sheet, 0, 0);

        SDL_RenderCopy(
            renderer,
            sprite_sheet.texture->texture,
            &src,
            NULL
        );

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(sprite_sheet.texture->texture);
    free(sprite_sheet.texture);
    sprite_sheet.texture = NULL;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window->window);
    free(window);
    window = NULL;

    SDL_Quit();
}
