#include "player_movement_input.h"

#include "../entity.h"
#include "../components/player.h"
#include "../components/character.h"
#include "../components/velocity.h"
#include "../components/sprite_animation.h"

#include "../managers/ecs_manager.h"


void reset_velocity(Velocity& velocity) {
    velocity.set_x(0);
    velocity.set_y(0);
}

void PlayerMovementInputSystem::update_entity(Entity& entity, Uint32 dt) {
    Player* player = m_ecs->get_component<Player>(entity);
    if (player == NULL) {
        return;
    }

    Velocity* _velocity = m_ecs->get_component<Velocity>(entity);
    if (_velocity == NULL) {
        return;
    }
    Velocity& velocity = *_velocity;

    Character* _character = m_ecs->get_component<Character>(entity);
    if (_character == NULL) {
        return;
    }
    Character& character = *_character;

    auto pressed_keys = m_input_manager->get_pressed_direction_keys();
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

        switch (key) {
            case SDLK_UP:
            reset_velocity(velocity);
            velocity.set_y(-1);
            character.set_orientation(Direction::UP);
            break;

            case SDLK_DOWN:
            reset_velocity(velocity);
            velocity.set_y(1);
            character.set_orientation(Direction::DOWN);
            break;

            case SDLK_LEFT:
            reset_velocity(velocity);
            velocity.set_x(-1);
            character.set_orientation(Direction::LEFT);
            break;

            case SDLK_RIGHT:
            reset_velocity(velocity);
            velocity.set_x(1);
            character.set_orientation(Direction::RIGHT);
            break;
        }

        character.set_character_state(CharacterState::MOVING);

        // return early once a direction has been set
        return;
    }

    // at this point, we've iterated through all the pressed keys and none of them were movement keys
    // ie. there should be no motion
    reset_velocity(velocity);
    character.set_character_state(CharacterState::IDLE);
}
