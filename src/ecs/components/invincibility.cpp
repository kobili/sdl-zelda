#include "invincibility.h"


Invincibility::Invincibility(Uint32 duration_ms) {
    m_duration_ms = duration_ms;

    m_timer_ms = 0;
}


void Invincibility::update_timer(Uint32 dt) {
    m_timer_ms += dt;
}


Uint32 Invincibility::get_duration() const {
    return m_duration_ms;
}


Uint32 Invincibility::get_elapsed_time() const {
    return m_timer_ms;
}
