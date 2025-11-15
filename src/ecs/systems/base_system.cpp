#include "base_system.h"

void ISystem::update() {
    for (auto& _entity : m_ecs->get_entities()) {
        Entity& entity = *_entity;
        update_entity(entity);
    }
}
