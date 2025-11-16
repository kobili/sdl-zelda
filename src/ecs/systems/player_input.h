#ifndef PLAYER_INPUT_SYSTEM_H
#define PLAYER_INPUT_SYSTEM_H

#include "base_system.h"


class PlayerInputSystem : public IInputSystem {
public:
    using IInputSystem::IInputSystem;

    void handle_input_for_entity(SDL_Event& e, Entity& entity) override;
};

#endif
