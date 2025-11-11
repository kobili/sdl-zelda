#include "camera.h"
#include "constants.h"


Camera::Camera(int x, int y) {
    m_x = x;
    m_y = y;

    m_w = NES_SCREEN_WIDTH;
    m_h = NES_SCREEN_HEIGHT;

    vel_x = 0;
    vel_y = 0;
}


void Camera::handle_event(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
            vel_y -= DEFAULT_CAMERA_SPEED;
            break;

            case SDLK_s:
            vel_y += DEFAULT_CAMERA_SPEED;
            break;

            case SDLK_a:
            vel_x -= DEFAULT_CAMERA_SPEED;
            break;

            case SDLK_d:
            vel_x += DEFAULT_CAMERA_SPEED;
            break;
        }
    }

    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
            vel_y += DEFAULT_CAMERA_SPEED;
            break;

            case SDLK_s:
            vel_y -= DEFAULT_CAMERA_SPEED;
            break;

            case SDLK_a:
            vel_x += DEFAULT_CAMERA_SPEED;
            break;

            case SDLK_d:
            vel_x -= DEFAULT_CAMERA_SPEED;
            break;
        }
    }
}


void Camera::move() {
    m_x += vel_x;
    if (m_x < 0) {
        m_x = 0;
    }

    if (m_x > OVERWORLD_WIDTH - NES_SCREEN_WIDTH) {
        m_x = OVERWORLD_WIDTH - NES_SCREEN_WIDTH;
    }

    m_y += vel_y;
    if (m_y < 0) {
        m_y = 0;
    }

    if (m_y > OVERWORLD_HEIGHT - NES_SCREEN_HEIGHT) {
        m_y = OVERWORLD_HEIGHT - NES_SCREEN_HEIGHT;
    }
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
