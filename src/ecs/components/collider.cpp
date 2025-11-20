#include "collider.h"


Collider::Collider(int w, int h) {
    m_hitbox.w = w;
    m_hitbox.h = h;
}


Collider::Collider(int x, int y, int w, int h) : Collider(w, h) {
    m_hitbox.x = x;
    m_hitbox.y = y;
}


Collider::Collider(int x, int y, int w, int h, ColliderType type) : Collider(x, y, w, h) {
    m_type = type;
}


SDL_Rect& Collider::get_hitbox() {
    return m_hitbox;
}


ColliderType Collider::get_type() const {
    return m_type;
}


void Collider::set_hitbox_position(int x, int y) {
    m_hitbox.x = x;
    m_hitbox.y = y;
}
