#include "camera.h"
#include "constants.h"


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


PanningCamera::PanningCamera(int x, int y, ObservableWindow* window) : Camera(x, y, window) {
    vel_x = 0;
    vel_y = 0;
}


void PanningCamera::handle_event(SDL_Event& e) {
    // TODO: make this snap to different zones instead of panning
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


ZoneCamera::ZoneCamera(int x, int y, ObservableWindow* window) : Camera(x, y, window) {
    next_zone = get_current_zone();
}


Zone Camera::get_current_zone() {
    int camera_center_x = m_x + (NES_SCREEN_WIDTH / 2);
    int camera_center_y = m_y + (NES_SCREEN_HEIGHT / 2);

    return {
        camera_center_x / NES_SCREEN_WIDTH,
        camera_center_y / NES_SCREEN_HEIGHT
    };
}


void ZoneCamera::handle_event(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        Zone current_zone = get_current_zone();

        switch (e.key.keysym.sym) {
            case SDLK_w:
            next_zone.row = current_zone.row - 1;
            if (next_zone.row < 0) {
                next_zone.row = current_zone.row;
            }
            break;

            case SDLK_s:
            next_zone.row = current_zone.row + 1;
            if (next_zone.row >= 8) {
                next_zone.row = current_zone.row;
            }
            break;

            case SDLK_a:
            next_zone.col = current_zone.col - 1;
            if (next_zone.col < 0) {
                next_zone.col = current_zone.col;
            }
            break;

            case SDLK_d:
            next_zone.col = current_zone.col + 1;
            if (next_zone.col >= 16) {
                next_zone.col = current_zone.col;
            }
            break;
        }
    }
}


void ZoneCamera::move() {
    m_x = next_zone.col * NES_SCREEN_WIDTH;
    m_y = next_zone.row * NES_SCREEN_HEIGHT;

    next_zone = get_current_zone();
}
