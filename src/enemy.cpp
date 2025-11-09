#include "enemy.h"

Enemy::Enemy() {
    x = 0;
    y = 0;
    vel_x = 0;
    vel_y = 0;

    sprite_sheet = NULL;
}

void Enemy::render(int scale_x, int scale_y) {
    // TODO: add a check for a null sprite sheet
    sprite_sheet->render_sprite(
        0,
        0,
        x * scale_x,
        y * scale_y,
        scale_x,
        scale_y
    );
}

void Enemy::set_sprite_sheet(SpriteSheet* sprite_sheet) {
    this->sprite_sheet = sprite_sheet;
}

void Enemy::set_x(int x) {
    this->x = x;
}

void Enemy::set_y(int y) {
    this->y = y;
}

void Enemy::move() {
    // stub
}
