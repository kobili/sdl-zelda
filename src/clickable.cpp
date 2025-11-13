#include "clickable.h"
#include "constants.h"
#include <cmath>


ClickHitbox::ClickHitbox(SDL_Rect collider, ObservableWindow* window, Camera* camera, ClickCallback on_click) {
    hitbox.x = collider.x;
    hitbox.y = collider.y;
    hitbox.w = collider.w;
    hitbox.h = collider.h;

    this->on_click = on_click;

    start_observing(window);
    this->camera = camera;
}


void ClickHitbox::on_window_resize(int w, int h) {
    screen_scale_x =  (double) w / (double) NES_SCREEN_WIDTH;
    screen_scale_y = (double) h / (double) NES_SCREEN_HEIGHT;
}


void ClickHitbox::update_position(int x, int y) {
    hitbox.x = x;
    hitbox.y = y;
}


void ClickHitbox::handle_event(SDL_Event& e) {
    if (e.type != SDL_MOUSEBUTTONDOWN) {
        return;
    }

    int screen_space_x = hitbox.x - camera->get_x();
    int screen_space_y = hitbox.y - camera->get_y();

    SDL_Rect screen_hitbox;
    screen_hitbox.x = std::round(screen_space_x * screen_scale_x);
    screen_hitbox.y = std::round(screen_space_y * screen_scale_y);
    screen_hitbox.w = std::round(hitbox.w * screen_scale_x);
    screen_hitbox.h = std::round(hitbox.h * screen_scale_y);

    bool inside = true;

    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    if (
        mouse_x < screen_hitbox.x
        || mouse_x > screen_hitbox.x + screen_hitbox.w
        || mouse_y < screen_hitbox.y
        || mouse_y > screen_hitbox.y + screen_hitbox.h
    ) {
        inside = false;
    }

    if (!inside) {
        return;
    }

    // printf(
    //     "screen_scale_x: %f, screen_scale_y: %f\n",
    //     screen_scale_x,
    //     screen_scale_y
    // );
    // printf(
    //     "screen_hitbox: {%d, %d, %d, %d}\n",
    //     screen_hitbox.x,
    //     screen_hitbox.y,
    //     screen_hitbox.w,
    //     screen_hitbox.h
    // );

    on_click(mouse_x, mouse_y);
}
