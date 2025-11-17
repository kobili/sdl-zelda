#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <vector>
#include "SDL.h"


struct SpriteAnimationFrame {
    // column and row on the sprite sheet
    int col;
    int row;

    // if the sprite should be flipped
    bool flip_horizontal;
    bool flip_vertical;
};


enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


class SpriteAnimation {
public:
    SpriteAnimation(
        Direction direction,
        int frame_duration_ms,
        std::vector<SpriteAnimationFrame> up_frames,
        std::vector<SpriteAnimationFrame> down_frames,
        std::vector<SpriteAnimationFrame> left_frames,
        std::vector<SpriteAnimationFrame> right_frames
    );
    SpriteAnimation(
        std::vector<SpriteAnimationFrame> up_frames,
        std::vector<SpriteAnimationFrame> down_frames,
        std::vector<SpriteAnimationFrame> left_frames,
        std::vector<SpriteAnimationFrame> right_frames
    );

    Direction get_direction();
    void set_direction(Direction dir);

    SpriteAnimationFrame get_current_frame();

    void update_timer(Uint32 dt);

    void start_animation();
    void stop_animation();

    bool is_animating();

private:
    Direction m_direction;

    Uint32 timer;

    bool m_is_animating;

    // how long to stay on a single frame
    int m_frame_duration_ms;

    std::vector<SpriteAnimationFrame> m_up_frames;
    std::vector<SpriteAnimationFrame> m_down_frames;
    std::vector<SpriteAnimationFrame> m_left_frames;
    std::vector<SpriteAnimationFrame> m_right_frames;
};


#endif
