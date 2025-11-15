#include "sprite_renderer.h"

#include "../components/position.h"
#include "../components/sprite.h"


SpriteRenderSystem::SpriteRenderSystem(
    ECSManager* ecs, TextureManager* texture_manager, Camera* camera, Window* window
) : ISystem(ecs) {
    m_texture_manager = texture_manager;
    m_camera = camera;
    m_window = window;
}

void SpriteRenderSystem::update_entity(Entity& entity) {
    Sprite* sprite = m_ecs->get_component<Sprite>(entity);
    if (sprite == NULL) {
        return;
    }
    Position* position = m_ecs->get_component<Position>(entity);
    if (position == NULL) {
        return;
    }
    Texture* texture = m_texture_manager->get_texture(sprite->get_texture_name());
    if (texture == NULL) {
        return;
    }

    SDL_Rect clip = sprite->get_sprite(0, 0);
    texture->render(
        position->get_x() - m_camera->get_x(),
        position->get_y() - m_camera->get_y(),
        &clip,
        m_window->get_scale_x(),
        m_window->get_scale_y()
    );
}
