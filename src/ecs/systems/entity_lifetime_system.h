#ifndef ENTITY_LIFETIME_SYSTEM_H
#define ENTITY_LIFETIME_SYSTEM_H

#include "SDL.h"

#include "base_system.h"


class EntityLifetimeSystem : public ISystem {
public:
    using ISystem::ISystem;
    void update_entity(Uint32 entity_id, Uint32 dt) override;
};

#endif
