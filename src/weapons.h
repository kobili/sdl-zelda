#include "constants.h"

#include "SDL.h"


struct Weapon {
    Uint32 attack_duration_ms;
};

// TODO: Maybe move this somewhere else
const Weapon WEAPONS[] = {
    // wooden sword
    {
        200
    },
    // white sword
    {
        BASE_LINK_ATTACK_DURATION_MS
    }
};

enum class WeaponValues {
    WOODEN_SWORD,
    WHITE_SWORD
};