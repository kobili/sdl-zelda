#include "sprite_animation.h"


SpriteAnimation::SpriteAnimation() {
    m_is_animating = true;
    timer = 0;
}


SpriteAnimationFrame SpriteAnimation::get_current_frame(CharacterState state, Direction direction) {
    AnimationSet animation_set = m_state_animation_map[state];
    int selected_frame = timer / animation_set.frame_duration_ms;
    
    std::vector<AnimationFrameData> direction_frames = animation_set.frames[(int) direction];

    return {
        direction_frames[selected_frame % direction_frames.size()]
    };
}


void SpriteAnimation::update_timer(Uint32 dt) {
    timer += dt;
}


void SpriteAnimation::start_animation() {
    m_is_animating = true;
}


void SpriteAnimation::stop_animation() {
    m_is_animating = false;
    timer = 0;
}


bool SpriteAnimation::is_animating() {
    return m_is_animating;
}


void SpriteAnimation::set_animation_set(CharacterState state, AnimationSet animation_set) {
    m_state_animation_map[state] = animation_set;
}
