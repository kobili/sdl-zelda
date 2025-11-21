#include "collider_system.h"

#include "../managers/ecs_manager.h"


ColliderDebugRenderSystem::ColliderDebugRenderSystem(
    ECSManager* ecs, Camera* camera, Window* window
) : ISystem(ecs) {
    m_camera = camera;
    m_window = window;
}


void ColliderDebugRenderSystem::update_entity(Uint32 entity, Uint32 dt) {
    Collider* _collider = m_ecs->get_component<Collider>(entity);
    if (!_collider) {
        return;
    }
    Collider collider = *_collider;

    Hurtbox* _hurtbox = m_ecs->get_component<Hurtbox>(entity);
    if (!_hurtbox) {
        return render_collider(collider);
    }
    Hurtbox hurtbox = *_hurtbox;

    render_hurtbox(collider, hurtbox);
}


void ColliderDebugRenderSystem::render_collider(Collider collider) {
    SDL_Rect hitbox = collider.get_hitbox();

    RGB colour = {0x00, 0xff, 0x00};

    render_rectangle(hitbox, colour, 0x60);
}


void ColliderDebugRenderSystem::render_hurtbox(Collider collider, Hurtbox hurtbox) {
    SDL_Rect hitbox = collider.get_hitbox();

    RGB colour = {0xff, 0xff, 0x00};  // yellow

    // if the hurtbox is active, change the colour to red
    if (hurtbox.is_active()) {
        colour.g = 0x00;
    }

    render_rectangle(hitbox, colour, 0x60);
}


void ColliderDebugRenderSystem::render_rectangle(SDL_Rect rect, RGB colour, Uint8 alpha) {
    // normalize the hitbox position and dimensions to the screen
    rect.x = std::round((rect.x - m_camera->get_x()) * m_window->get_scale_x());
    rect.y = std::round((rect.y - m_camera->get_y()) * m_window->get_scale_y());
    rect.w = std::round(rect.w * m_window->get_scale_x());
    rect.h = std::round(rect.h * m_window->get_scale_y());

    SDL_Renderer* renderer = m_window->get_renderer();
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, alpha);
    SDL_RenderFillRect(renderer, &rect);
}
