#include "window.h"
#include "constants.h"


Window::Window() {
    m_window = NULL;
    m_renderer = NULL;

    m_w = 0;
    m_h = 0;
}


Window::~Window() {
    free();
    printf("Destroyed window\n");
}


bool Window::init() {
    m_window = SDL_CreateWindow(
        "Zeldeep",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (m_window == NULL) {
        printf("failed to create window: %s\n", SDL_GetError());
        return false;
    }

    m_w = SCREEN_WIDTH;
    m_h = SCREEN_HEIGHT;

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == NULL) {
        printf("Failed to get renderer: %s\n", SDL_GetError());

        SDL_DestroyWindow(m_window);
        m_window = NULL;
        return false;
    }

    return true;
}


void Window::free() {
    SDL_DestroyRenderer(m_renderer);
    m_renderer = NULL;

    SDL_DestroyWindow(m_window);
    m_window = NULL;

    m_w = 0;
    m_h = 0;
}


SDL_Renderer* Window::get_renderer() {
    return m_renderer;
}


int Window::get_width() {
    return m_w;
}


int Window::get_height() {
    return m_h;
}
