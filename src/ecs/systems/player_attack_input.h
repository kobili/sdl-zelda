#ifndef PLAYER_ATTACK_INPUT_SYSTEM_H
#define PLAYER_ATTACK_INPUT_SYSTEM_H

#include "base_system.h"


class PlayerAttackInputSystem : public IInputSystem {
public:
    using IInputSystem::IInputSystem;

    void virtual handle_input_for_entity(SDL_Event& e, Entity& entity);
};

#endif
