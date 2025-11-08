#include "window.h"
#include "constants.h"


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

void free_window(Window* window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);

    printf("destroyed window\n");
}
