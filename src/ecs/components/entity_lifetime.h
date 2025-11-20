#ifndef ENTITY_LIFETIME_H
#define ENTITY_LIFETIME_H

#include "SDL.h"


class EntityLifetime {
public:
    EntityLifetime(Uint32 lifetime_ms);

    void update_age(Uint32 dt);

    Uint32 get_lifetime_ms();
    Uint32 get_age_ms();

private:
    Uint32 m_lifetime_ms;
    Uint32 m_age_ms;
};

#endif
