#ifndef HURTBOX_H
#define HURTBOX_H

#include "SDL.h"


// Use in conjunction with Collider
class Hurtbox {
public:
    Hurtbox(
        int damage_value,
        Uint32 duration_ms,
        Uint32 active_start_time_ms,
        Uint32 active_end_time_ms
    );

    int get_damage_value() const;

    Uint32 get_active_start_time() const;
    Uint32 get_active_end_time() const;
    Uint32 get_duration() const;

    Uint32 get_elapsed_time() const;
    void update_timer(Uint32 dt);

    bool is_active() const;

private:
    int m_damage_value;

    // how long the hurtbox should exist
    Uint32 m_duration_ms;

    // the start and end times when the hurtbox is active
    Uint32 m_active_start_time_ms;
    Uint32 m_active_end_time_ms;

    // internal timer
    Uint32 m_timer_ms;
};

#endif
