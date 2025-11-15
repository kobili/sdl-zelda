#ifndef COLLIDER_H
#define COLLIDER_H

#include "SDL.h"


class Collider {
public:
    Collider(int w, int h);
    Collider(int x, int y, int w, int h);

    SDL_Rect& get_hitbox();

    void set_hitbox_position(int x, int y);
private:
    SDL_Rect m_hitbox;
};

#endif
