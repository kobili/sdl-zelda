#include "panning_camera.h"
#include "../constants.h"


PanningCamera::PanningCamera(int x, int y) : Camera(x, y) {
    vel_x = 0;
    vel_y = 0;
}


void PanningCamera::handle_event(SDL_Event& e) {
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


void PanningCamera::move() {
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
