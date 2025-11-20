#ifndef COLLIDER_H
#define COLLIDER_H

#include "SDL.h"


enum class ColliderType {
    OBSTACLE,
    PUSHABLE,
    EPHEMERAL, // for things like hitboxes
};


class Collider {
public:
    Collider(int w, int h);
    Collider(int x, int y, int w, int h);
    Collider(int x, int y, int w, int h, ColliderType type);

    SDL_Rect& get_hitbox();

    void set_hitbox_position(int x, int y);

    ColliderType get_type() const;
private:
    SDL_Rect m_hitbox;
    ColliderType m_type;
};

#endif
