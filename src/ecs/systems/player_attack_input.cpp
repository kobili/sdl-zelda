#include "player_attack_input.h"

#include "../components/player.h"
#include "../components/movement.h"
#include "../components/velocity.h"
#include "../components/character.h"
#include "../components/sprite_animation.h"

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

        printf("Attacked\n");
    }
}
