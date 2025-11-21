#ifndef HURTBOX_H
#define HURTBOX_H

#include "SDL.h"


// Use in conjunction with Collider
class Hurtbox {
public:
    Hurtbox(Uint32 duration_ms, Uint32 active_start_time_ms, Uint32 active_end_time_ms);

    Uint32 get_active_start_time() const;
    Uint32 get_active_end_time() const;
    Uint32 get_duration() const;

    Uint32 get_elapsed_time() const;
    void update_timer(Uint32 dt);

    bool is_active() const;

private:
    // how long the hurtbox should exist
    Uint32 m_duration_ms;

    // the start and end times when the hurtbox is active
    Uint32 m_active_start_time_ms;
    Uint32 m_active_end_time_ms;

    // internal timer
    Uint32 m_timer_ms;
};

#endif
