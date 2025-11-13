#ifndef ZONE_CAMERA_H
#define ZONE_CAMERA_H

#include "camera.h"


class ZoneCamera : public Camera {
public:
    ZoneCamera(int x, int y);
    void handle_event(SDL_Event& e) override;
    void move() override;

private:
    Zone next_zone;
};

#endif
