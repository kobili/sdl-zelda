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

void SpriteRenderSystem::update() {
    for (const std::unique_ptr<Entity>& _entity : m_ecs->get_entities()) {
        Entity& entity = *_entity;

        Sprite* sprite = m_ecs->get_component<Sprite>(entity);
        if (sprite == NULL) {
            continue;
        }
        Position* position = m_ecs->get_component<Position>(entity);
        if (position == NULL) {
            continue;
        }
        Texture* texture = m_texture_manager->get_texture(sprite->get_texture_name());
        if (texture == NULL) {
            continue;
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
}
