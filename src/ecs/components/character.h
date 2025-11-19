#ifndef CHARACTER_H
#define CHARACTER_H

#include "SDL.h"

#include "../../constants.h"


class Character {
public:
    Character();
    Character(Direction orientation, CharacterState state);
    Character(Direction orientation, CharacterState state, Uint32 attack_duration_ms);

    Direction get_orientation();
    void set_orientation(Direction orientation);

    CharacterState get_character_state();
    void set_character_state(CharacterState state);

    Uint32 get_time_in_state_ms();
    void update_time_in_state(Uint32 dt);

    /**
     * Return how long it takes to complete an attack
     */
    Uint32 get_attack_duration_ms();

private:
    Direction m_orientation;
    CharacterState m_state;

    Uint32 m_time_in_state_ms;

    Uint32 m_attack_duration_ms;
};

#endif
