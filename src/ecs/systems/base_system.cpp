#include "base_system.h"

#include "../managers/ecs_manager.h"

void ISystem::update(Uint32 dt) {
    for (auto& _entity : m_ecs->get_entities()) {
        update_entity(_entity, dt);
    }
}
