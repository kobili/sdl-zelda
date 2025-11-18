#ifndef PLAYER_INPUT_SYSTEM_H
#define PLAYER_INPUT_SYSTEM_H

#include "base_system.h"


class PlayerInputSystem : public IInputSystem {
public:
    using IInputSystem::IInputSystem;

    void virtual update_entity(Entity& entity, Uint32 dt) override;
};

#endif
