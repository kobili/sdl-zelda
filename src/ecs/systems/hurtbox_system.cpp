#include "hurtbox_system.h"

#include <cmath>

#include "../components/hurtbox.h"
#include "../components/collider.h"

#include "../managers/ecs_manager.h"
#include "../../texture.h"


void HurtboxIncrementSystem::update_entity(int entity, Uint32 dt) {
    Hurtbox* _hurtbox = m_ecs->get_component<Hurtbox>(entity);
    if (!_hurtbox) {
        return;
    }
    Hurtbox& hurtbox = *_hurtbox;

    hurtbox.update_timer(dt);

    if (hurtbox.get_elapsed_time() >= hurtbox.get_duration()) {
        m_ecs->mark_remove(entity);
    }
}


HurtboxDebugRenderSystem::HurtboxDebugRenderSystem(
    ECSManager* ecs, Camera* camera, Window* window
) : ISystem(ecs) {
    m_camera = camera;
    m_window = window;
}


void HurtboxDebugRenderSystem::update_entity(int entity, Uint32 dt) {
    Hurtbox* _hurtbox = m_ecs->get_component<Hurtbox>(entity);
    if (!_hurtbox) {
        return;
    }
    Hurtbox hurtbox = *_hurtbox;

    Collider* _collider = m_ecs->get_component<Collider>(entity);
    if (!_collider) {
        return;
    }
    Collider collider = *_collider;

    SDL_Rect hitbox = collider.get_hitbox();

    RGB colour = {0xff, 0xff, 0x00};  // yellow

    // if the hurtbox is active, change the colour to red
    if (
        hurtbox.get_elapsed_time() >= hurtbox.get_active_start_time()
        && hurtbox.get_elapsed_time() < hurtbox.get_active_end_time()
    ) {
        colour.g = 0x00;
    }

    // normalize the hitbox position and dimensions to the screen
    hitbox.x = std::round((hitbox.x - m_camera->get_x()) * m_window->get_scale_x());
    hitbox.y = std::round((hitbox.y - m_camera->get_y()) * m_window->get_scale_y());
    hitbox.w = std::round(hitbox.w * m_window->get_scale_x());
    hitbox.h = std::round(hitbox.h * m_window->get_scale_y());

    SDL_Renderer* renderer = m_window->get_renderer();
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 0x60);
    SDL_RenderFillRect(renderer, &hitbox);
}
