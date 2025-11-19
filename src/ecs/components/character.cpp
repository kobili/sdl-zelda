#include "character.h"


Character::Character() {
    m_orientation = Direction::DOWN;
    m_state = CharacterState::IDLE;

    m_time_in_state_ms = 0;
    m_attack_duration_ms = 0;
}


Character::Character(Direction orientation, CharacterState state) : Character() {
    m_orientation = orientation;
    m_state = state;
}

Character::Character(
    Direction orientation,
    CharacterState state,
    Uint32 attack_duration_ms
) : Character(orientation, state) {
    m_attack_duration_ms = attack_duration_ms;
}



Direction Character::get_orientation() {
    return m_orientation;
}


void Character::set_orientation(Direction orientation) {
    m_orientation = orientation;
}


CharacterState Character::get_character_state() {
    return m_state;
}


void Character::set_character_state(CharacterState state) {
    m_state = state;
    m_time_in_state_ms = 0;
}


Uint32 Character::get_time_in_state_ms() {
    return m_time_in_state_ms;
}


void Character::update_time_in_state(Uint32 dt) {
    m_time_in_state_ms += dt;
}


Uint32 Character::get_attack_duration_ms() {
    return m_attack_duration_ms;
}
