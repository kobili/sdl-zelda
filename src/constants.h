#ifndef CONSTANTS_H
#define CONSTANTS_H

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 352;

const int NES_SCREEN_WIDTH = 256;
const int NES_SCREEN_HEIGHT = 176;

const int OVERWORLD_SCREEN_COLUMNS = 16;
const int OVERWORLD_SCREEN_ROWS = 8;

const int OVERWORLD_WIDTH = NES_SCREEN_WIDTH * 16;
const int OVERWORLD_HEIGHT = NES_SCREEN_HEIGHT * 8;


const int LINK_ATTACK_DURATION_MS = 300;


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
