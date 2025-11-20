#include "entity.h"


Entity::Entity(int id) {
    m_id = id;
}


int Entity::get_id() const {
    return m_id;
}
