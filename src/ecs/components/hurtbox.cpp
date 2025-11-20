#include "hurtbox.h"


Hurtbox::Hurtbox(Uint32 duration_ms, Uint32 active_start_time_ms, Uint32 active_end_time_ms) {
    m_duration_ms = duration_ms;
    m_active_start_time_ms = active_start_time_ms;
    m_active_end_time_ms = active_end_time_ms;

    m_timer_ms = 0;
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
