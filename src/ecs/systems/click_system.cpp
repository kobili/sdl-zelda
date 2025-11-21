#include "click_system.h"

#include <cmath>
#include "SDL.h"

#include "../components/collider.h"
#include "../components/clickable.h"
#include "../managers/ecs_manager.h"


ClickSystem::ClickSystem(
    ECSManager* manager,
    InputManager* input_manager,
    Window* window,
    Camera* camera
) : IInputSystem(manager, input_manager) {
    m_window = window;
    m_camera = camera;
}


void ClickSystem::update_entity(Uint32 entity_id, Uint32 dt) {
    auto mouse_events = m_input_manager->get_mouse_events();

    if (mouse_events.size() == 0) {
        return;
    }

    Clickable* _clickable = m_ecs->get_component<Clickable>(entity_id);
    if (_clickable == NULL) {
        return;
    }
    Clickable clickable = *_clickable;

    Collider* _collider = m_ecs->get_component<Collider>(entity_id);
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

    for (auto& mouse_event : mouse_events) {
        if (mouse_event.type != MouseEventType::BUTTONDOWN) {
            continue;
        }

        if (
            mouse_event.x < screen_hitbox.x
            || mouse_event.x > screen_hitbox.x + screen_hitbox.w
            || mouse_event.y < screen_hitbox.y
            || mouse_event.y > screen_hitbox.y + screen_hitbox.h
        ) {
            // mouse outside of hitbox; stop execution
            continue;
        }

        ClickHandler callback = clickable.get_callback();
        callback(entity_id);
    }
}
