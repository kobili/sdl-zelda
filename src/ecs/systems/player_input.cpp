#include "player_input.h"

#include "../entity.h"
#include "../components/player.h"
#include "../components/movement.h"
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


void handle_movement_inputs(SDL_Event& e, Velocity& velocity, SpriteAnimation* animation) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        Direction new_direction = animation != NULL ? animation->get_direction() : Direction::UP;

        switch (e.key.keysym.sym) {
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
    }

    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_DOWN:
            velocity.set_y(0);
            break;

            case SDLK_LEFT:
            case SDLK_RIGHT:
            velocity.set_x(0);
            break;
        }

        // read key states and transition motion to whatever key is still being pressed
        Direction new_direction = Direction::DOWN;
        bool set_direction = false;
        
        const Uint8* key_states = SDL_GetKeyboardState(NULL);
        if (key_states[SDL_SCANCODE_UP]) {
            velocity.set_y(-1);
            new_direction = Direction::UP;
            set_direction = true;
        } else if (key_states[SDL_SCANCODE_DOWN]) {
            velocity.set_y(1);
            new_direction = Direction::DOWN;
            set_direction = true;
        } else if (key_states[SDL_SCANCODE_LEFT]) {
            velocity.set_x(-1);
            new_direction = Direction::LEFT;
            set_direction = true;
        } else if (key_states[SDL_SCANCODE_RIGHT]) {
            velocity.set_x(1);
            new_direction = Direction::RIGHT;
            set_direction = true;
        }

        if (set_direction) {
            update_animation_direction(animation, new_direction);
        }
    }
}


void PlayerInputSystem::handle_input_for_entity(SDL_Event& e, Entity& entity) {
    Player* player = m_ecs->get_component<Player>(entity);
    if (player == NULL) {
        return;
    }

    Movement* movement = m_ecs->get_component<Movement>(entity);
    if (movement == NULL) {
        return;
    }

    Velocity* _velocity = m_ecs->get_component<Velocity>(entity);
    if (_velocity == NULL) {
        return;
    }
    Velocity& velocity = *_velocity;

    SpriteAnimation* animation = m_ecs->get_component<SpriteAnimation>(entity);

    handle_movement_inputs(e, velocity, animation);

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_f:
            reset_velocity(velocity);
            printf("Attacked\n");
            break;
        }
    }

    if (animation != NULL) {
        if (velocity.in_motion()) {
            animation->start_animation();
        } else {
            animation->stop_animation();
        }
    }
}
