#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "base_system.h"

class MovementSystem : public ISystem {
public:
    using ISystem::ISystem;

    void virtual update_entity(Entity& entity) override;
};

#endif
