#include "player_attack_input.h"

#include "../../constants.h"

#include "../components/player.h"
#include "../components/moveable.h"
#include "../components/velocity.h"
#include "../components/character.h"
#include "../components/collider.h"
#include "../components/hurtbox.h"
#include "../components/position.h"

#include "../managers/ecs_manager.h"


void PlayerAttackInputSystem::update_entity(int entity_id, Uint32 dt) {
    Player* player = m_ecs->get_component<Player>(entity_id);
    if (player == NULL) {
        return;
    }

    Character* _character = m_ecs->get_component<Character>(entity_id);
    if (!_character) {
        return;
    }
    Character& character = *_character;

    if (character.get_character_state() == CharacterState::ATTACKING) {
        return;
    }

    auto key_presses = m_input_manager->get_keyboard_events();
    auto key_binds = m_input_manager->get_keybinds();

    for (auto& key_press : key_presses) {
        if (key_press.key_code != key_binds[Action::ATTACK]) {
            continue;
        }
        if (key_press.type != KeyboardEventType::BUTTONDOWN) {
            continue;
        }

        character.set_character_state(CharacterState::ATTACKING);

        std::function<void()> create_hurtbox = [this, &entity_id]() {
            create_sword_hurtbox(*this->m_ecs, entity_id);
            printf("created sword hitbox\n");
        };

        m_ecs->add_operation(create_hurtbox);

        printf("Attacked\n");
    }
}


void create_sword_hurtbox(ECSManager& ecs, int player_entity) {
    Position* _player_position = ecs.get_component<Position>(player_entity);
    if (!_player_position) {
        return;
    }
    Position player_position = *_player_position;

    Character* _player_character = ecs.get_component<Character>(player_entity);
    if (!_player_character) {
        return;
    }
    Character player_character = *_player_character;

    int entity_id = 23;  // TODO: should unhardcode this
    ecs.add_entity(entity_id);

    ecs.add_component<Hurtbox>(entity_id, Hurtbox(
        3 * LINK_ATTACK_ANIMATION_FRAME_DURATION_MS,
        LINK_ATTACK_ANIMATION_FRAME_DURATION_MS,
        2 * LINK_ATTACK_ANIMATION_FRAME_DURATION_MS
    ));

    int collider_x = player_position.get_x();
    int collider_y = player_position.get_y();
    int collider_w, collider_h;

    switch (player_character.get_orientation()) {
        case Direction::UP:
        collider_x += 2;
        collider_y -= 12;
        collider_w = 9;
        collider_h = 12;
        break;

        case Direction::DOWN:
        collider_x += 4;
        collider_y += 16;
        collider_w = 9;
        collider_h = 11;
        break;

        case Direction::LEFT:
        collider_y += 5;
        collider_w = 11;
        collider_h = 9;
        collider_x -= collider_w;
        break;

        case Direction::RIGHT:
        collider_x += 16;
        collider_y += 5;
        collider_w = 11;
        collider_h = 9;
        break;
    }

    ecs.add_component<Collider>(
        entity_id,
        Collider(
            collider_x,
            collider_y,
            collider_w,
            collider_h,
            ColliderType::EPHEMERAL
        )
    );
}
