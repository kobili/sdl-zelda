#include "hurtbox.h"


Hurtbox::Hurtbox(
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
}

int Hurtbox::get_damage_value() const {
    return m_damage_value;
}

Uint32 Hurtbox::get_active_start_time() const {
    return m_active_start_time_ms;
}

Uint32 Hurtbox::get_active_end_time() const {
    return m_active_end_time_ms;
}

Uint32 Hurtbox::get_duration() const {
    return m_duration_ms;
}

Uint32 Hurtbox::get_elapsed_time() const {
    return m_timer_ms;
}

void Hurtbox::update_timer(Uint32 dt) {
    m_timer_ms += dt;
}

bool Hurtbox::is_active() const {
    return (
        m_timer_ms >= m_active_start_time_ms
        && m_timer_ms < m_active_end_time_ms
    );
}

void Hurtbox::touch_entity(Uint32 entity_id) {
    m_touched_entities.insert(entity_id);
}

bool Hurtbox::has_entity_been_touched(Uint32 entity_id) {
    return m_touched_entities.count(entity_id) != 0;
}
