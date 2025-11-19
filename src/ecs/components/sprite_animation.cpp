#include "sprite_animation.h"


SpriteAnimation::SpriteAnimation() {
    m_timer = 0;
}


SpriteAnimationFrame SpriteAnimation::get_current_frame(CharacterState state, Direction direction, Uint32 timer) {
    AnimationSet animation_set = m_state_animation_map[state];
    int selected_frame = timer / animation_set.frame_duration_ms;
    
    std::vector<AnimationFrameData> direction_frames = animation_set.frames[(int) direction];

    return {
        direction_frames[selected_frame % direction_frames.size()]
    };
}


SpriteAnimationFrame SpriteAnimation::get_current_frame(CharacterState state, Direction direction) {
    return get_current_frame(state, direction, m_timer);
}


void SpriteAnimation::update_timer(Uint32 dt) {
    m_timer += dt;
}



void SpriteAnimation::set_animation_set(CharacterState state, AnimationSet animation_set) {
    m_state_animation_map[state] = animation_set;
}
