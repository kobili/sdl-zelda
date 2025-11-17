#include "sprite_renderer.h"

#include "../components/position.h"
#include "../components/sprite.h"
#include "../components/sprite_animation.h"
#include "../managers/ecs_manager.h"


SpriteRenderSystem::SpriteRenderSystem(
    ECSManager* ecs, TextureManager* texture_manager, Camera* camera, Window* window
) : ISystem(ecs) {
    m_texture_manager = texture_manager;
    m_camera = camera;
    m_window = window;
}

void SpriteRenderSystem::update_entity(Entity& entity, Uint32 dt) {
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

    SpriteAnimation* animation = m_ecs->get_component<SpriteAnimation>(entity);
    SDL_Rect clip;
    bool flip_horizontal = false;
    if (animation != NULL) {
        SpriteAnimationFrame frame = animation->get_current_frame();
        flip_horizontal = frame.flip_horizontal;
        clip = sprite->get_sprite(frame.col, frame.row);
    } else {
        clip = sprite->get_sprite(0, 0);
    }

    texture->render(
        position->get_x() - m_camera->get_x(),
        position->get_y() - m_camera->get_y(),
        &clip,
        m_window->get_scale_x(),
        m_window->get_scale_y(),
        flip_horizontal
    );
}
