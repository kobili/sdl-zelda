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

    Direction new_direction = animation != NULL ? animation->get_direction() : Direction::UP;

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            velocity.add_y(-1);
            new_direction = Direction::UP;
            break;

            case SDLK_DOWN:
            velocity.add_y(1);
            new_direction = Direction::DOWN;
            break;

            case SDLK_LEFT:
            velocity.add_x(-1);
            new_direction = Direction::LEFT;
            break;

            case SDLK_RIGHT:
            velocity.add_x(1);
            new_direction = Direction::RIGHT;
            break;
        }

        update_animation_direction(animation, new_direction);
    }

    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            velocity.add_y(1);
            break;

            case SDLK_DOWN:
            velocity.add_y(-1);;
            break;

            case SDLK_LEFT:
            velocity.add_x(1);
            break;

            case SDLK_RIGHT:
            velocity.add_x(-1);
            break;
        }
    }
}
