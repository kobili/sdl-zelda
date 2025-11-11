#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include <vector>

#include "observer.h"

class Window : public Observable {
public:
    Window();
    ~Window();

    bool init();
    void free();

    SDL_Renderer* get_renderer();

    int get_width();
    int get_height();

    void handle_event(SDL_Event& e);

    void add_observer(Observer* observer) override; 
    void notify_observers() override;

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    int m_w, m_h;
};

#endif
