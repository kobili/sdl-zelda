#include "player_input.h"

#include "../entity.h"
#include "../components/player.h"
#include "../components/velocity.h"
#include "../components/sprite_animation.h"

#include "../managers/ecs_manager.h"


void update_animation_direction(SpriteAnimation* _animation, Direction new_direction) {
    if (_animation == NULL) {
        return;
    }
    SpriteAnimation& animation = *_animation;

    if (new_direction == animation.get_direction()) {
        return;
    }

    animation.set_direction(new_direction);
}


void reset_velocity(Velocity& velocity) {
    velocity.set_x(0);
    velocity.set_y(0);
}

void PlayerInputSystem::update_entity(Entity& entity, Uint32 dt) {
    Player* player = m_ecs->get_component<Player>(entity);
    if (player == NULL) {
        return;
    }

    Velocity* _velocity = m_ecs->get_component<Velocity>(entity);
    if (_velocity == NULL) {
        return;
    }
    Velocity& velocity = *_velocity;

    SpriteAnimation* animation = m_ecs->get_component<SpriteAnimation>(entity);


    auto pressed_keys = m_input_manager->get_pressed_keys();
    auto key_binds = m_input_manager->get_keybinds();

    for (SDL_Keycode key : pressed_keys) {
        if (
            key != key_binds[Action::WALK_UP]
            && key != key_binds[Action::WALK_DOWN]
            && key != key_binds[Action::WALK_LEFT]
            && key != key_binds[Action::WALK_RIGHT]
        ) {
            continue;
        }

        Direction new_direction = animation != NULL ? animation->get_direction() : Direction::UP;

        switch (key) {
            case SDLK_UP:
            reset_velocity(velocity);
            velocity.set_y(-1);
            new_direction = Direction::UP;
            break;

            case SDLK_DOWN:
            reset_velocity(velocity);
            velocity.set_y(1);
            new_direction = Direction::DOWN;
            break;

            case SDLK_LEFT:
            reset_velocity(velocity);
            velocity.set_x(-1);
            new_direction = Direction::LEFT;
            break;

            case SDLK_RIGHT:
            reset_velocity(velocity);
            velocity.set_x(1);
            new_direction = Direction::RIGHT;
            break;
        }

        update_animation_direction(animation, new_direction);
        if (animation != NULL) {
            animation->start_animation();
        }

        // return early once a direction has been set
        return;
    }

    // at this point, we've iterated through all the pressed keys and none of them were movement keys
    // ie. there should be no motion
    reset_velocity(velocity);
    if (animation != NULL) {
        animation->stop_animation();
    }
}
