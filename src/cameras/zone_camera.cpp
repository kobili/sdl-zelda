#include "zone_camera.h"
#include "../constants.h"


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

