#include "entity_lifetime_system.h"

#include "../managers/ecs_manager.h"
#include "../components/entity_lifetime.h"


void EntityLifetimeSystem::update_entity(Entity& entity, Uint32 dt) {
    EntityLifetime* _lifetime = m_ecs->get_component<EntityLifetime>(entity);
    if (!_lifetime) {
        return;
    }
    EntityLifetime& lifetime = *_lifetime;

    lifetime.update_age(dt);

    if (lifetime.get_age_ms() >= lifetime.get_lifetime_ms()) {
        entity.deactivate();
        printf("Deactivated Entity %d\n", entity.get_id());
    }
}
