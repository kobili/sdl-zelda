#ifndef CHARACTER_UPDATE_H
#define CHARACTER_UPDATE_H

#include "base_system.h"


class CharacterUpdateSystem : public ISystem {
public:
    using ISystem::ISystem;

    void update_entity(Entity& entity, Uint32 dt) override;
};

#endif
