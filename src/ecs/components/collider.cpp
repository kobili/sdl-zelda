#include "collider.h"


Collider::Collider(int w, int h) {
    m_hitbox.w = w;
    m_hitbox.h = h;
}


Collider::Collider(int x, int y, int w, int h) : Collider(w, h) {
    m_hitbox.x = x;
    m_hitbox.y = y;
}


SDL_Rect& Collider::get_hitbox() {
    return m_hitbox;
}


void Collider::set_hitbox_position(int x, int y) {
    m_hitbox.x = x;
    m_hitbox.y = y;
}
