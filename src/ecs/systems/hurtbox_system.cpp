#include "hurtbox_system.h"

#include "../components/hurtbox.h"
#include "../managers/ecs_manager.h"


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
