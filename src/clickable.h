#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "SDL.h"
#include "observers/window_observer.h"
#include "camera.h"


typedef void (*ClickCallback) (int, int);


class Clickable : public WindowObserver {
public:
    /**
     * \param x The x coordinate in world space
     * \param y The y coordinate in world space
     * \param width The base width of the hitbox
     * \param height The base height of the hitbox
     */
    Clickable(int x, int y, int width, int height);

    void on_window_resize(int w, int h) override;

    /**
     * Update the position of the clickable in world space
     * 
     * \param x The x coordinate in world space
     * \param y The y coordinate in world space
     */
    void update_position(int x, int y);

private:
    // coordinates and dimensions in world space
    int world_x, world_y;
    int base_width, base_height;

    // coordinates on the screen
    int screen_x, screen_y;

    SDL_Rect hitbox;
};


class ClickHitbox : public WindowObserver {
public:
    ClickHitbox(SDL_Rect collider, ObservableWindow* window, Camera* camera, ClickCallback on_click);
    void on_window_resize(int w, int h) override;

    void update_position(int x, int y);

    void handle_event(SDL_Event& e);

private:
    SDL_Rect hitbox;
    Camera* camera;  // non-owning

    int screen_scale_x, screen_scale_y;

    ClickCallback on_click;
};

#endif
