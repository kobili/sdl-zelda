#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <vector>
#include <map>
#include <string>

#include "SDL.h"

#include "../../constants.h"


struct AnimationFrameData {
    // column and row on the sprite sheet
    int col;
    int row;

    // if the sprite should be flipped
    bool flip_horizontal;
    bool flip_vertical;
};


struct SpriteAnimationFrame {
    AnimationFrameData frame_data;
};


struct AnimationSet {
    // how long each frame should last
    int frame_duration_ms;

    // the SpriteAnimation frames for the animation for all 4 directions
    // ordered: UP, DOWN, LEFT, RIGHT
    std::vector<AnimationFrameData> frames[4];
};


class SpriteAnimation {
public:
    SpriteAnimation();

    SpriteAnimationFrame get_current_frame(CharacterState state, Direction direction, Uint32 timer);

    void update_timer(Uint32 dt);

    void start_animation();
    void stop_animation();

    bool is_animating();

    /**
     * \param state The character state for which the animation will play
     * \param animation_set The animation set corresponding to the character state
     */
    void set_animation_set(CharacterState state, AnimationSet animation_set);

private:
    Uint32 m_timer;

    bool m_is_animating;

    std::map<CharacterState, AnimationSet> m_state_animation_map;
};


#endif
