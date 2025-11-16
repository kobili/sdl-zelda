#include "camera.h"
#include "../constants.h"


Camera::Camera(int x, int y) {
    m_x = x;
    m_y = y;

    m_w = NES_SCREEN_WIDTH;
    m_h = NES_SCREEN_HEIGHT;
}


int Camera::get_x() {
    return m_x;
}


int Camera::get_y() {
    return m_y;
}


SDL_Rect Camera::get_collider() {
    return {m_x, m_y, m_w, m_h};
}
