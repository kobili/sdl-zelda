#ifndef CAMERA_H
#define CAMERA_H

#include "SDL.h"
#include "../utils.h"


class Camera {
public:
    Camera(int x, int y);
    virtual ~Camera() = default;

    void virtual handle_event(SDL_Event& e) = 0;
    void virtual move() = 0;

    int get_x();
    int get_y();
    double get_scale_x();
    double get_scale_y();

    SDL_Rect get_collider();

    /**
     * Retrieve the zone that the camera is currently showing.
     * 
     * Uses the position of the center of the camera to determine the zone.
     */
    Zone get_current_zone();

protected:
    // location of the upper left corner of the camera in world space
    int m_x, m_y;
    int m_w, m_h;

    double scale_x, scale_y;
};

#endif
