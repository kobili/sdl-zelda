#include "click_system.h"

#include <cmath>
#include "SDL.h"

#include "../components/collider.h"
#include "../components/clickable.h"
#include "../managers/ecs_manager.h"


ClickSystem::ClickSystem(ECSManager* manager, Window* window, Camera* camera) : IInputSystem(manager) {
    m_window = window;
    m_camera = camera;
}


void ClickSystem::handle_input_for_entity(SDL_Event& e, Entity& entity) {
    if (e.type != SDL_MOUSEBUTTONDOWN) {
        return;
    }

    Clickable* _clickable = m_ecs->get_component<Clickable>(entity);
    if (_clickable == NULL) {
        return;
    }
    Clickable clickable = *_clickable;

    Collider* _collider = m_ecs->get_component<Collider>(entity);
    if (_collider == NULL) {
        return;
    }
    Collider collider = *_collider;

    SDL_Rect hitbox = collider.get_hitbox();

    int screen_space_x = hitbox.x - m_camera->get_x();
    int screen_space_y = hitbox.y - m_camera->get_y();

    SDL_Rect screen_hitbox;
    screen_hitbox.x = std::round(screen_space_x * m_window->get_scale_x());
    screen_hitbox.y = std::round(screen_space_y * m_window->get_scale_y());
    screen_hitbox.w = std::round(hitbox.w * m_window->get_scale_x());
    screen_hitbox.h = std::round(hitbox.h * m_window->get_scale_y());

    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    if (
        mouse_x < screen_hitbox.x
        || mouse_x > screen_hitbox.x + screen_hitbox.w
        || mouse_y < screen_hitbox.y
        || mouse_y > screen_hitbox.y + screen_hitbox.h
    ) {
        // mouse outside of hitbox; stop execution
        return;
    }

    ClickHandler callback = clickable.get_callback();
    callback(entity);
}
