#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include <vector>

class Window {
public:
    Window();
    ~Window();

    bool init();
    void free();

    SDL_Renderer* get_renderer();

    int get_width();
    int get_height();

    void handle_event(SDL_Event& e);

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    int m_w, m_h;
    double scale_x, scale_y;
};

#endif
