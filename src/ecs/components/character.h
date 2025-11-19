#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../constants.h"


class Character {
public:
    Character();
    Character(Direction orientation, CharacterState state);

    Direction get_orientation();
    void set_orientation(Direction orientation);

    CharacterState get_character_state();
    void set_character_state(CharacterState state);

private:
    Direction m_orientation;
    CharacterState m_state;
};

#endif
