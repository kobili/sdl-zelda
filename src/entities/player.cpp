#include "player.h"

#include "../constants.h"
#include "../utils.h"


Player::Player(SpriteSheet* sprite, ObservableWindow* window, Camera* camera) : Entity(sprite) {
    std::unique_ptr<ClickHitbox> _click_hitbox (
        new ClickHitbox(
            m_collider,
            window,
            camera,
            player_on_click
        )
    );

    click_hitbox = std::move(_click_hitbox);
}


void Player::handle_event(SDL_Event& e) {
    click_hitbox->handle_event(e);

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

    click_hitbox->update_position(x, y);
}


Zone Player::get_current_zone() {
    return {
        x / NES_SCREEN_WIDTH,
        y / NES_SCREEN_HEIGHT
    };
}

void player_on_click(int x, int y) {
    printf("Player (%d, %d)\n", x, y);
}


void Player::set_x(int x) {
    Entity::set_x(x);
    click_hitbox->update_position(this->x, this->y);
}

void Player::set_y(int y) {
    Entity::set_y(y);
    click_hitbox->update_position(this->x, this->y);
}
