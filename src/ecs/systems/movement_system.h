#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <vector>

#include "base_system.h"

class MovementSystem : public ISystem {
public:
    using ISystem::ISystem;

    void virtual update_entity(int entity_id, Uint32 dt) override;

private:
    std::vector<SDL_Rect*> get_other_colliders(int entity_id);
};

#endif
