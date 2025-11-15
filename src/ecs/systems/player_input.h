#ifndef PLAYER_INPUT_SYSTEM_H
#define PLAYER_INPUT_SYSTEM_H

#include "base_system.h"


class PlayerInputSystem : IInputSystem {
public:
    using IInputSystem::IInputSystem;

    void handle_input(SDL_Event& e) override;
};

#endif
