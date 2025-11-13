#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "SDL.h"
#include "observers/window_observer.h"
#include "cameras/camera.h"


class ClickHitbox : public WindowObserver {
public:
    ClickHitbox(SDL_Rect collider, ObservableWindow* window, Camera* camera);
    void on_window_resize(int w, int h) override;

    void update_position(int x, int y);

    bool detect_click(SDL_Event& e);

private:
    SDL_Rect hitbox;
    Camera* camera;  // non-owning

    double screen_scale_x, screen_scale_y;
};

#endif
