#include "sprite_renderer.h"

#include "../components/position.h"
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
    Position* position = m_ecs->get_component<Position>(entity_id);
    if (position == NULL) {
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

    SpriteInformation sprite_info = animation.get_sprite_info();

    Texture* texture = m_texture_manager->get_texture(sprite_info.texture_name);
    if (texture == NULL) {
        return;
    }

    AnimationFrameData frame = animation.get_current_frame(character.get_character_state(), character.get_orientation(), character.get_time_in_state_ms());
    
    SDL_Rect clip = animation.get_sprite(frame.col, frame.row);

    int x = position->get_x() + frame.offset_x;
    int y = position->get_y() + frame.offset_y;

    texture->render(
        x - m_camera->get_x(),
        y - m_camera->get_y(),
        &clip,
        m_window->get_scale_x(),
        m_window->get_scale_y(),
        frame.flip_horizontal,
        frame.flip_vertical
    );
}
