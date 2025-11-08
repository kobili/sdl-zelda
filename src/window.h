#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"

struct Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

Window* create_window();

void free_window(Window* window);

#endif
