#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <vector>

#include "base_system.h"

class MovementSystem : public ISystem {
public:
    using ISystem::ISystem;

    void virtual update_entity(Entity& entity) override;

private:
    std::vector<SDL_Rect*> get_other_colliders(Entity& entity);
};

#endif
