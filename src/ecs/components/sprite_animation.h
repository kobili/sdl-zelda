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

    int offset_x;
    int offset_y;
};


struct SpriteAnimationFrame {
    AnimationFrameData frame_data;
};


struct AnimationSet {
    // how long each frame should last
    int frame_duration_ms;

    // whether or not the animation should continue to loop
    bool looping;

    // the SpriteAnimation frames for the animation for all 4 directions
    // ordered: UP, DOWN, LEFT, RIGHT
    std::vector<AnimationFrameData> frames[4];
};

class CharacterAnimation {
public:
    CharacterAnimation();

    SpriteAnimationFrame get_current_frame(CharacterState state, Direction direction, Uint32 timer);

    /*
    * Overloaded method to use internal timer instead
    */
    SpriteAnimationFrame get_current_frame(CharacterState state, Direction direction);

    void update_timer(Uint32 dt);

    /**
     * \param state The character state for which the animation will play
     * \param animation_set The animation set corresponding to the character state
     */
    void set_animation_set(CharacterState state, AnimationSet animation_set);

private:
    Uint32 m_timer;

    std::map<CharacterState, AnimationSet> m_state_animation_map;
};


struct SpriteInformation {
    std::string texture_name;
    int sprite_width_px;
    int sprite_height_px;
};


// component solely for animating Link's sword
// link it to the player entity
class SwordAnimation {
public:
    SwordAnimation(SpriteInformation sprite_info, AnimationSet animation_set);

    /**
     * \param direction The direction link is facing while attacking
     * \param timer The time in which link has been in the attacking state
     */
    AnimationFrameData get_animation_frame(Direction direction, Uint32 timer);

    SpriteInformation& get_sprite_info();

private:
    SpriteInformation m_sprite_info;
    AnimationSet m_animation_set;
};


#endif
