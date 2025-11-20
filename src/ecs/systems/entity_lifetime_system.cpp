#include "entity_lifetime_system.h"

#include "../managers/ecs_manager.h"
#include "../components/entity_lifetime.h"


void EntityLifetimeSystem::update_entity(int entity_id, Uint32 dt) {
    EntityLifetime* _lifetime = m_ecs->get_component<EntityLifetime>(entity_id);
    if (!_lifetime) {
        return;
    }
    EntityLifetime& lifetime = *_lifetime;

    lifetime.update_age(dt);

    if (lifetime.get_age_ms() >= lifetime.get_lifetime_ms()) {
        m_ecs->mark_remove(entity_id);
        printf("Marked Entity %d for removal\n", entity_id);
    }
}
