#ifndef HURTBOX_H
#define HURTBOX_H

#include <unordered_set>

#include "SDL.h"


class ContactHurtbox {
public:
    ContactHurtbox(int damage_value);

    int get_damage_value() const;

private:
    int m_damage_value;
};


/**
 * Component detailing the hurtboxes attached to things that should only damage an entity once in its lifetime
 * ie. sword strikes, arrows, fireballs.
 * 
 * Use in conjunction with a `Collider` component for position and width info
 */
class AttackHurtbox {
public:
    AttackHurtbox(int damage_value);

    AttackHurtbox(
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

    void touch_entity(Uint32 entity_id);
    bool has_entity_been_touched(Uint32 entity_id);

    bool is_permanent() const;

private:
    int m_damage_value;

    // how long the hurtbox should exist
    Uint32 m_duration_ms;

    // the start and end times when the hurtbox is active
    Uint32 m_active_start_time_ms;
    Uint32 m_active_end_time_ms;

    bool m_is_permanently_active;

    // internal timer
    Uint32 m_timer_ms;

    std::unordered_set<Uint32> m_touched_entities;
};

#endif
