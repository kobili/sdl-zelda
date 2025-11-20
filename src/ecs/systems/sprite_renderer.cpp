#include "sprite_renderer.h"

#include "../components/position.h"
#include "../components/sprite.h"
#include "../components/sprite_animation.h"
#include "../components/character.h"
#include "../managers/ecs_manager.h"


CharacterSpriteRenderSystem::CharacterSpriteRenderSystem(
    ECSManager* ecs, TextureManager* texture_manager, Camera* camera, Window* window
) : ISystem(ecs) {
    m_texture_manager = texture_manager;
    m_camera = camera;
    m_window = window;
}

// TODO: Split this into Player and Enemy character render systems so we can render with priority Player->Sword->Enemy
void CharacterSpriteRenderSystem::update_entity(int entity_id, Uint32 dt) {
    // TODO: Remove dependency on sprite. Sprite info should be embedded in CharacterAnimation à la SwordAnimation
    Sprite* sprite = m_ecs->get_component<Sprite>(entity_id);
    if (sprite == NULL) {
        return;
    }
    Position* position = m_ecs->get_component<Position>(entity_id);
    if (position == NULL) {
        return;
    }

    Texture* texture = m_texture_manager->get_texture(sprite->get_texture_name());
    if (texture == NULL) {
        return;
    }

    Character* _character = m_ecs->get_component<Character>(entity_id);
    if (!_character) {
        return;
    }
    Character& character = *_character;

    CharacterAnimation* _animation = m_ecs->get_component<CharacterAnimation>(entity_id);
    if (!_animation) {
        return;
    }
    CharacterAnimation& animation = *_animation;

    SpriteAnimationFrame frame = animation.get_current_frame(character.get_character_state(), character.get_orientation(), character.get_time_in_state_ms());
    SDL_Rect clip = sprite->get_sprite(frame.frame_data.col, frame.frame_data.row);

    int x = position->get_x() + frame.frame_data.offset_x;
    int y = position->get_y() + frame.frame_data.offset_y;

    texture->render(
        x - m_camera->get_x(),
        y - m_camera->get_y(),
        &clip,
        m_window->get_scale_x(),
        m_window->get_scale_y(),
        frame.frame_data.flip_horizontal,
        frame.frame_data.flip_vertical
    );
}
