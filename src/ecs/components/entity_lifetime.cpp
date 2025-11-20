#include "entity_lifetime.h"


EntityLifetime::EntityLifetime(Uint32 lifetime_ms) {
    m_age_ms = 0;
    m_lifetime_ms = lifetime_ms;
}


void EntityLifetime::update_age(Uint32 dt) {
    m_age_ms += dt;
}


Uint32 EntityLifetime::get_lifetime_ms() {
    return m_lifetime_ms;
}


Uint32 EntityLifetime::get_age_ms() {
    return m_age_ms;
}
