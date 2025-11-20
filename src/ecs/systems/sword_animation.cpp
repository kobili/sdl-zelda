#include "sword_animation.h"

#include "../managers/ecs_manager.h"

#include "../components/sprite_animation.h"
#include "../components/character.h"
#include "../components/position.h"
#include "../components/player.h"


SwordAnimationSystem::SwordAnimationSystem(ECSManager* ecs, TextureManager* texture_manager, Camera* camera, Window* window) : ISystem(ecs) {
    m_camera = camera;
    m_window = window;
    m_texture_manager = texture_manager;
}


void SwordAnimationSystem::update_entity(int entity_id, Uint32 dt) {
    Player* _player = m_ecs->get_component<Player>(entity_id);
    if (!_player) {
        return;
    }

    Character* _character = m_ecs->get_component<Character>(entity_id);
    if (!_character) {
        return;
    }
    Character character = *_character;

    if (character.get_character_state() != CharacterState::ATTACKING) {
        return;
    }

    Position* _position = m_ecs->get_component<Position>(entity_id);
    if (!_position) {
        return;
    }
    Position& position = *_position;

    SwordAnimation* _sword_animation = m_ecs->get_component<SwordAnimation>(entity_id);
    if (!_sword_animation) {
        return;
    }
    SwordAnimation& sword_animation = *_sword_animation;

    AnimationFrameData current_frame = sword_animation.get_animation_frame(character.get_orientation(), character.get_time_in_state_ms());

    SpriteInformation sprite_info = sword_animation.get_sprite_info();

    // see Sprite.get_sprite
    SDL_Rect clip = sword_animation.get_sprite(current_frame.col, current_frame.row);

    int x = position.get_x() + current_frame.offset_x;
    int y = position.get_y() + current_frame.offset_y;

    Texture* texture = m_texture_manager->get_texture(sprite_info.texture_name);
    if (!texture) {
        printf("Failed to render sword attack: missing texture %s\n", sprite_info.texture_name.c_str());
        return;
    }

    texture->render(
        x - m_camera->get_x(),
        y - m_camera->get_y(),
        &clip,
        m_window->get_scale_x(),
        m_window->get_scale_y(),
        current_frame.flip_horizontal,
        current_frame.flip_vertical
    );
}
