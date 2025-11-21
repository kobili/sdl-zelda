#ifndef HURTBOX_SYSTEM_H
#define HURTBOX_SYSTEM_H

#include "base_system.h"

#include "../../cameras/camera.h"
#include "../../window.h"


class AttackHurtboxIncrementSystem : public ISystem {
public:
    using ISystem::ISystem;
    void update_entity(Uint32 entity, Uint32 dt) override;
};


class AttackDamageDetectionSystem : public ISystem {
public:
    using ISystem::ISystem;
    void update_entity(Uint32 entity, Uint32 dt) override;
};

#endif
