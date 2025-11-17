#include "sprite_animation.h"


SpriteAnimation::SpriteAnimation(
    Direction direction,
    int rate_of_change,
    std::vector<SpriteAnimationFrame> up_frames,
    std::vector<SpriteAnimationFrame> down_frames,
    std::vector<SpriteAnimationFrame> left_frames,
    std::vector<SpriteAnimationFrame> right_frames
) : SpriteAnimation(up_frames, down_frames, left_frames, right_frames) {
    m_direction = direction;
    m_rate_of_change = rate_of_change;
}


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

    m_is_animating = false;

    timer = 0;

    m_rate_of_change = 100;
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
    int selected_frame = timer / m_rate_of_change;

    switch (m_direction) {
        case Direction::UP:
        return m_up_frames[selected_frame % m_up_frames.size()];

        case Direction::DOWN:
        return m_down_frames[selected_frame % m_up_frames.size()];
        
        case Direction::RIGHT:
        return m_right_frames[selected_frame % m_up_frames.size()];

        case Direction::LEFT:
        return m_left_frames[selected_frame % m_up_frames.size()];
    }
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
