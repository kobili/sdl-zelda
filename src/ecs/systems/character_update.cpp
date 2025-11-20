#include "character_update.h"

#include "../managers/ecs_manager.h"

#include "../components/character.h"


void CharacterUpdateSystem::update_entity(int entity_id, Uint32 dt) {
    Character* _character = m_ecs->get_component<Character>(entity_id);
    if (_character == NULL) {
        return;
    }
    Character& character = *_character;

    character.update_time_in_state(dt);

    if (
        character.get_character_state() == CharacterState::ATTACKING
        && character.get_time_in_state_ms() >= character.get_attack_duration_ms()
    ) {
        character.set_character_state(CharacterState::IDLE);
    }
}
