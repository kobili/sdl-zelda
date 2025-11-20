#include "entity.h"


Entity::Entity(int id) {
    m_id = id;
    m_is_active = true;
}


int Entity::get_id() const {
    return m_id;
}

bool Entity::is_active() const {
    return m_is_active;
}

void Entity::deactivate() {
    m_is_active = false;
}
