#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "SDL.h"
#include "observers/window_observer.h"
#include "cameras/camera.h"


typedef void (*ClickCallback) (int, int);


class ClickHitbox : public WindowObserver {
public:
    ClickHitbox(SDL_Rect collider, ObservableWindow* window, Camera* camera, ClickCallback on_click);
    void on_window_resize(int w, int h) override;

    void update_position(int x, int y);

    void handle_event(SDL_Event& e);

private:
    SDL_Rect hitbox;
    Camera* camera;  // non-owning

    double screen_scale_x, screen_scale_y;

    ClickCallback on_click;
};

#endif
