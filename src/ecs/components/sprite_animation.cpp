#include "sprite_animation.h"


CharacterAnimation::CharacterAnimation() {
    m_timer = 0;
}


SpriteAnimationFrame CharacterAnimation::get_current_frame(CharacterState state, Direction direction, Uint32 timer) {
    AnimationSet animation_set = m_state_animation_map[state];
    int selected_frame = timer / animation_set.frame_duration_ms;
    
    std::vector<AnimationFrameData> direction_frames = animation_set.frames[(int) direction];
    selected_frame = selected_frame % direction_frames.size();

    if (!animation_set.looping) {
        if (selected_frame >= direction_frames.size()) {
            selected_frame = direction_frames.size() - 1;
        }
    }

    return {
        direction_frames[selected_frame]
    };
}


SpriteAnimationFrame CharacterAnimation::get_current_frame(CharacterState state, Direction direction) {
    return get_current_frame(state, direction, m_timer);
}


void CharacterAnimation::update_timer(Uint32 dt) {
    m_timer += dt;
}


void CharacterAnimation::set_animation_set(CharacterState state, AnimationSet animation_set) {
    m_state_animation_map[state] = animation_set;
}


SwordAnimation::SwordAnimation(SpriteInformation sprite_info, AnimationSet animation_set) {
    m_sprite_info = sprite_info;
    m_animation_set = animation_set;
}


AnimationFrameData SwordAnimation::get_animation_frame(Direction direction, Uint32 timer) {
    int selected_frame = timer / m_animation_set.frame_duration_ms;

    std::vector<AnimationFrameData> direction_frames = m_animation_set.frames[(int) direction];

    if (selected_frame == direction_frames.size()) {
        selected_frame = direction_frames.size() - 1;
    }

    return direction_frames[selected_frame];
}


SpriteInformation& SwordAnimation::get_sprite_info() {
    return m_sprite_info;
}
