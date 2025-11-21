#include "hurtbox.h"


AttackHurtbox::AttackHurtbox(int damage_value) {
    m_damage_value = damage_value;

    m_timer_ms = 0;
    m_is_permanently_active = true;

    m_duration_ms = 0;
    m_active_start_time_ms = 0;
    m_active_end_time_ms = 0;
}


AttackHurtbox::AttackHurtbox(
    int damage_value,
    Uint32 duration_ms,
    Uint32 active_start_time_ms,
    Uint32 active_end_time_ms
) {
    m_damage_value = damage_value;
    m_duration_ms = duration_ms;
    m_active_start_time_ms = active_start_time_ms;
    m_active_end_time_ms = active_end_time_ms;

    m_timer_ms = 0;

    m_is_permanently_active = false;
}

int AttackHurtbox::get_damage_value() const {
    return m_damage_value;
}

Uint32 AttackHurtbox::get_active_start_time() const {
    return m_active_start_time_ms;
}

Uint32 AttackHurtbox::get_active_end_time() const {
    return m_active_end_time_ms;
}

Uint32 AttackHurtbox::get_duration() const {
    return m_duration_ms;
}

Uint32 AttackHurtbox::get_elapsed_time() const {
    return m_timer_ms;
}

void AttackHurtbox::update_timer(Uint32 dt) {
    m_timer_ms += dt;
}

bool AttackHurtbox::is_active() const {
    return m_is_permanently_active || (
        m_timer_ms >= m_active_start_time_ms
        && m_timer_ms < m_active_end_time_ms
    );
}

void AttackHurtbox::touch_entity(Uint32 entity_id) {
    m_touched_entities.insert(entity_id);
}

bool AttackHurtbox::has_entity_been_touched(Uint32 entity_id) {
    return m_touched_entities.count(entity_id) != 0;
}

bool AttackHurtbox::is_permanent() const {
    return m_is_permanently_active;
}
