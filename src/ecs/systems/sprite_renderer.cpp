#include "sprite_renderer.h"

#include "../components/position.h"
#include "../components/sprite.h"
#include "../components/sprite_animation.h"
#include "../components/character.h"
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

    Character* character = m_ecs->get_component<Character>(entity);

    SpriteAnimation* animation = m_ecs->get_component<SpriteAnimation>(entity);
    SDL_Rect clip;
    bool flip_horizontal = false;
    bool flip_vertical = false;
    if (animation != NULL && character != NULL) {
        SpriteAnimationFrame frame = animation->get_current_frame(character->get_character_state(), character->get_orientation());
        flip_horizontal = frame.frame_data.flip_horizontal;
        flip_vertical = frame.frame_data.flip_vertical;
        clip = sprite->get_sprite(frame.frame_data.col, frame.frame_data.row);
    } else {
        clip = sprite->get_sprite(0, 0);
    }

    texture->render(
        position->get_x() - m_camera->get_x(),
        position->get_y() - m_camera->get_y(),
        &clip,
        m_window->get_scale_x(),
        m_window->get_scale_y(),
        flip_horizontal,
        flip_vertical
    );
}
