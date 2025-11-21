#include "entity_lifetime_system.h"

#include "../managers/ecs_manager.h"
#include "../components/entity_lifetime.h"
#include "../components/invincibility.h"


void EntityLifetimeSystem::update_entity(Uint32 entity_id, Uint32 dt) {
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


void InvincibilityLifetimeSystem::update_entity(Uint32 entity_id, Uint32 dt) {
    Invincibility* _invincibility = m_ecs->get_component<Invincibility>(entity_id);
    if (!_invincibility) {
        return;
    }
    Invincibility& invincibility = *_invincibility;

    invincibility.update_timer(dt);

    if (invincibility.get_elapsed_time() > invincibility.get_duration()) {
        m_ecs->remove_component({
            entity_id, std::type_index(typeid(Invincibility))
        });
    }
}
