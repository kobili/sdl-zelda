#ifndef INVINCIBILITY_COMPONENT_H
#define INVINCIBILITY_COMPONENT_H

#include "SDL.h"


class Invincibility {
public:
    Invincibility(Uint32 duration_ms);

    void update_timer(Uint32 dt);
    Uint32 get_duration() const;
    Uint32 get_elapsed_time() const;

private:
    Uint32 m_duration_ms;
    Uint32 m_timer_ms;
};

#endif
