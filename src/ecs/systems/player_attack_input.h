#ifndef PLAYER_ATTACK_INPUT_SYSTEM_H
#define PLAYER_ATTACK_INPUT_SYSTEM_H

#include "base_system.h"


class PlayerAttackInputSystem : public IInputSystem {
public:
    using IInputSystem::IInputSystem;

    void virtual update_entity(Entity& entity, Uint32 dt) override;
};

#endif
