#ifndef SWORD_ANIMATION_H
#define SWORD_ANIMATION_H


#include "base_system.h"


class SwordAnimationSystem : public ISystem {
public:
    using ISystem::ISystem;
    void update_entity(Entity& entity, Uint32 dt) override;
};

#endif
