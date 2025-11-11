#ifndef CAMERA_H
#define CAMERA_H

#include "SDL.h"

const int DEFAULT_CAMERA_SPEED = 5;

class Camera {
public:
    Camera(int x, int y);
    void handle_event(SDL_Event& e);

    void move();

    int get_x();
    int get_y();

    SDL_Rect get_collider();

private:
    // location of the upper left corner of the camera in world space
    int m_x, m_y;
    int m_w, m_h;
    int vel_x, vel_y;
};

#endif
