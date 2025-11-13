#include "clickable.h"
#include "constants.h"

Clickable::Clickable(int x, int y, int width, int height) {
    world_x = x;
    world_y = y;

    base_width = width;
    base_height = height;

    hitbox.x = x;
    hitbox.y = y;
    hitbox.w = width;
    hitbox.h = height;

    // null values for now
    screen_x = 0;
    screen_y = 0;
}


void Clickable::on_window_resize(int w, int h) {
    double scale_x =  (double) w / (double) NES_SCREEN_WIDTH;
    double scale_y = (double) h / (double) NES_SCREEN_HEIGHT;

    hitbox.w = hitbox.w * scale_x;
    hitbox.h = hitbox.h * scale_y;
}


void Clickable::update_position(int x, int y) {
    hitbox.x = x;
    hitbox.y = y;
}
