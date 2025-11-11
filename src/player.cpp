#include "player.h"

#include "constants.h"
#include "utils.h"


void Player::handle_event(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            vel_y -= DEFAULT_VELOCITY;
            break;

            case SDLK_DOWN:
            vel_y += DEFAULT_VELOCITY;
            break;

            case SDLK_LEFT:
            vel_x -= DEFAULT_VELOCITY;
            break;

            case SDLK_RIGHT:
            vel_x += DEFAULT_VELOCITY;
            break;
        }
    }

    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            vel_y += DEFAULT_VELOCITY;
            break;

            case SDLK_DOWN:
            vel_y -= DEFAULT_VELOCITY;
            break;

            case SDLK_LEFT:
            vel_x += DEFAULT_VELOCITY;
            break;

            case SDLK_RIGHT:
            vel_x -= DEFAULT_VELOCITY;
            break;
        }
    }
}


void Player::move(std::vector<SDL_Rect*> colliders) {
    x += vel_x;
    update_collider();

    if (x < 0 || x > OVERWORLD_WIDTH - m_sprite_sheet->get_sprite_width() || check_collisions(m_collider, colliders)) {
        x -= vel_x;
    }

    y += vel_y;
    update_collider();

    if (y < 0 || y > OVERWORLD_HEIGHT - m_sprite_sheet->get_sprite_height() || check_collisions(m_collider, colliders)) {
        y -= vel_y;
    }
}
