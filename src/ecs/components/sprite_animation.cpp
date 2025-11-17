#include "sprite_animation.h"


SpriteAnimation::SpriteAnimation(
    std::vector<SpriteAnimationFrame> up_frames,
    std::vector<SpriteAnimationFrame> down_frames,
    std::vector<SpriteAnimationFrame> left_frames,
    std::vector<SpriteAnimationFrame> right_frames
) {
    m_up_frames = up_frames;
    m_down_frames = down_frames;
    m_left_frames = left_frames;
    m_right_frames = right_frames;

    m_direction = Direction::DOWN;
}


Direction SpriteAnimation::get_direction() {
    return m_direction;
}


void SpriteAnimation::set_direction(Direction dir) {
    m_direction = dir;

    // reset the animation on direction change
    timer = 0;
}


SpriteAnimationFrame SpriteAnimation::get_current_frame() {
    // TODO: make this select specific frames based on the timer
    switch (m_direction) {
        case Direction::UP:
        return m_up_frames[0];

        case Direction::DOWN:
        return m_down_frames[0];
        
        case Direction::RIGHT:
        return m_right_frames[0];

        case Direction::LEFT:
        return m_left_frames[0];
    }
}


void SpriteAnimation::update_timer(Uint32 dt) {
    timer += dt;
}


void SpriteAnimation::reset_timer() {
    timer = 0;
}
