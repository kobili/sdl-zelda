#ifndef CAMERA_H
#define CAMERA_H

#include "SDL.h"
#include "window_observer.h"
#include "window.h"
#include "utils.h"


const int DEFAULT_CAMERA_SPEED = 5;

class Camera : WindowObserver {
public:
    Camera(int x, int y, ObservableWindow* window);
    void handle_event(SDL_Event& e);

    void move();

    int get_x();
    int get_y();
    double get_scale_x();
    double get_scale_y();

    SDL_Rect get_collider();

    void on_window_resize(int w, int h) override;

    /**
     * Shfit the camera to center on the given zone.
     * The top left corner of the camera will be placed on that zone's top left corner
     */
    void shift_to_zone(Zone zone);

    /**
     * Retrieve the zone that the camera is currently showing.
     * 
     * Uses the position of the center of the camera to determine the zone.
     */
    Zone get_current_zone();

private:
    // location of the upper left corner of the camera in world space
    int m_x, m_y;
    int m_w, m_h;
    int vel_x, vel_y;

    double scale_x, scale_y;
};

#endif
