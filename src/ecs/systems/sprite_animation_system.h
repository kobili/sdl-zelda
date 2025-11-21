#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

#include "base_system.h"

class SpriteAnimationSystem : public ISystem {
public:
    using ISystem::ISystem;

    void update_entity(Uint32 entity_id, Uint32 dt) override;
};

#endif
