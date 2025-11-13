#include "camera.h"
#include "../constants.h"


Camera::Camera(int x, int y, ObservableWindow* window) {
    m_x = x;
    m_y = y;

    m_w = NES_SCREEN_WIDTH;
    m_h = NES_SCREEN_HEIGHT;

    scale_x = 1;
    scale_y = 1;

    start_observing(window);
}


int Camera::get_x() {
    return m_x;
}


int Camera::get_y() {
    return m_y;
}


double Camera::get_scale_x() {
    return scale_x;
}


double Camera::get_scale_y() {
    return scale_y;
}


SDL_Rect Camera::get_collider() {
    return {m_x, m_y, m_w, m_h};
}


void Camera::on_window_resize(int w, int h) {
    scale_x =  (double) w / (double) NES_SCREEN_WIDTH;
    scale_y = (double) h / (double) NES_SCREEN_HEIGHT;
}
