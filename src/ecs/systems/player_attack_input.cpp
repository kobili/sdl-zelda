#include "player_attack_input.h"

#include "../components/player.h"
#include "../components/movement.h"
#include "../components/velocity.h"
#include "../components/character.h"
#include "../components/sprite_animation.h"

#include "../managers/ecs_manager.h"


void PlayerAttackInputSystem::update_entity(Entity& entity, Uint32 dt) {
    Player* player = m_ecs->get_component<Player>(entity);
    if (player == NULL) {
        return;
    }

    Character* character = m_ecs->get_component<Character>(entity);

    auto key_presses = m_input_manager->get_keyboard_events();
    auto key_binds = m_input_manager->get_keybinds();

    for (auto& key_press : key_presses) {
        if (key_press.key_code != key_binds[Action::ATTACK]) {
            continue;
        }
        if (key_press.type != KeyboardEventType::BUTTONDOWN) {
            continue;
        }

        if (character) {
            character->set_character_state(CharacterState::ATTACKING);
        }

        printf("Attacked\n");
    }
}
