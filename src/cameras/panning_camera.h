#ifndef PANNING_CAMERA_H
#define PANNING_CAMERA_H

#include "camera.h"


const int DEFAULT_CAMERA_SPEED = 5;


class PanningCamera : public Camera {
public:
    PanningCamera(int x, int y);
    void handle_event(SDL_Event& e) override;
    void move() override;

private:
    int vel_x, vel_y;
};

#endif
