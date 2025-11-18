#ifndef PLAYER_MOVEMENT_INPUT_SYSTEM_H
#define PLAYER_MOVEMENT_INPUT_SYSTEM_H

#include "base_system.h"


class PlayerMovementInputSystem : public IInputSystem {
public:
    using IInputSystem::IInputSystem;

    void virtual update_entity(Entity& entity, Uint32 dt) override;
};

#endif
