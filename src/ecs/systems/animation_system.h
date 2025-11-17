#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

#include "base_system.h"

class AnimationSystem : public ISystem {
public:
    using ISystem::ISystem;

    void update_entity(Entity& entity, Uint32 dt) override;
};

#endif
