#ifndef PLAYER_ATTACK_INPUT_SYSTEM_H
#define PLAYER_ATTACK_INPUT_SYSTEM_H

#include "base_system.h"


class PlayerAttackInputSystem : public IInputSystem {
public:
    using IInputSystem::IInputSystem;

    void virtual update_entity(Uint32 entity_id, Uint32 dt) override;

private:
    void create_sword_hurtbox(Uint32 player_entity);
};

#endif
