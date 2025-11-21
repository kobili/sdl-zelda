#include "hurtbox_system.h"

#include <cmath>

#include "../components/hurtbox.h"
#include "../components/collider.h"
#include "../components/character.h"

#include "../managers/ecs_manager.h"
#include "../../texture.h"
#include "../../utils.h"


void HurtboxIncrementSystem::update_entity(int entity, Uint32 dt) {
    Hurtbox* _hurtbox = m_ecs->get_component<Hurtbox>(entity);
    if (!_hurtbox) {
        return;
    }
    Hurtbox& hurtbox = *_hurtbox;

    hurtbox.update_timer(dt);

    if (hurtbox.get_elapsed_time() >= hurtbox.get_duration()) {
        m_ecs->mark_remove(entity);
    }
}


void DamageDetectionSystem::update_entity(int entity, Uint32 dt) {
    Character* _character = m_ecs->get_component<Character>(entity);
    if (!_character) {
        return;
    }

    Collider* _collider = m_ecs->get_component<Collider>(entity);
    if (!_collider) {
        return;
    }
    Collider collider = *_collider;

    for (int other_entity : m_ecs->get_entities()) {
        if (other_entity == entity) {
            continue;
        }

        Hurtbox* _hurtbox = m_ecs->get_component<Hurtbox>(other_entity);
        if (!_hurtbox) {
            continue;
        }
        Hurtbox hurtbox = *_hurtbox;

        if (!hurtbox.is_active()) {
            continue;
        }

        Collider* _other_collider = m_ecs->get_component<Collider>(other_entity);
        if (!_other_collider) {
            continue;
        }
        Collider other_collider = *_other_collider;

        if ( !check_collision(collider.get_hitbox(), other_collider.get_hitbox()) ) {
            continue;
        }

        printf("Entity %d: Took %d damage\n", entity, hurtbox.get_damage_value());
    }
}
