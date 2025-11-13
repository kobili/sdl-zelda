#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "SDL.h"
#include "window_observer.h"


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

#endif
