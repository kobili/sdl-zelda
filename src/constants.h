#ifndef CONSTANTS_H
#define CONSTANTS_H

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 704;

const int NES_SCREEN_WIDTH = 256;
const int NES_SCREEN_HEIGHT = 176;

const int OVERWORLD_SCREEN_COLUMNS = 16;
const int OVERWORLD_SCREEN_ROWS = 8;

const int OVERWORLD_WIDTH = NES_SCREEN_WIDTH * 16;
const int OVERWORLD_HEIGHT = NES_SCREEN_HEIGHT * 8;


const int LINK_ATTACK_DURATION_MS = 500;
const int LINK_ATTACK_ANIMATION_FRAMES = 4;
const int LINK_ATTACK_ANIMATION_FRAME_DURATION_MS = (
    LINK_ATTACK_DURATION_MS / LINK_ATTACK_ANIMATION_FRAMES
);

// time in ms during link's attack animation that the hitbox is active
// pretty coupled to the attack animation; it lines up to when the sword is all the way out (see sprite sheet)
const int LINK_ATTACK_HITBOX_ACTIVE_START_TIME_MS = LINK_ATTACK_ANIMATION_FRAME_DURATION_MS;
const int LINK_ATTACK_HITBOX_ACTIVE_END_TIME_MS = 2 * LINK_ATTACK_ANIMATION_FRAME_DURATION_MS;


// when attacking down, link's sword sticks downwards 11 past his sprite

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


enum class CharacterState {
    IDLE,
    MOVING,
    ATTACKING
};

#endif
