#include "character.h"


Character::Character() {
    m_orientation = Direction::DOWN;
    m_state = CharacterState::IDLE;
}


Character::Character(Direction orientation, CharacterState state) {
    m_orientation = orientation;
    m_state = state;
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
}
