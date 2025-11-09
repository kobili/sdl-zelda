#include "player.h"

#include "constants.h"
#include "utils.h"


Player::Player() {
    x = 0;
    y = 0;
    vel_x = 0;
    vel_y = 0;

    collider.x = 0;
    collider.y = 0;
}


int Player::get_x() {
    return x;
}


int Player::get_y() {
    return y;
}


void Player::set_sprite_sheet(SpriteSheet* sprite_sheet) {
    m_sprite_sheet = sprite_sheet;

    collider.w = sprite_sheet->get_sprite_width();
    collider.h = sprite_sheet->get_sprite_height();
}


void Player::render(int scale_x, int scale_y) {
    // TODO: add a check for a null sprite_sheet
    m_sprite_sheet->render_sprite(
        0,
        0,
        x * scale_x,
        y * scale_y,
        scale_x,
        scale_y
    );
}


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

    if (x < 0 || x > NES_SCREEN_WIDTH - m_sprite_sheet->get_sprite_width() || check_collisions(collider, colliders)) {
        x -= vel_x;
    }

    y += vel_y;
    update_collider();

    if (y < 0 || y > NES_SCREEN_HEIGHT - m_sprite_sheet->get_sprite_height() || check_collisions(collider, colliders)) {
        y -= vel_y;
    }
}

SDL_Rect& Player::get_collider() {
    return collider;
}

void Player::update_collider() {
    collider.x = x;
    collider.y = y;
}
