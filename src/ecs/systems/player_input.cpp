#include "player_input.h"

#include "../entity.h"
#include "../components/player.h"
#include "../components/movement.h"
#include "../components/velocity.h"
#include "../managers/ecs_manager.h"


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

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            velocity.add_y(-1);
            break;

            case SDLK_DOWN:
            velocity.add_y(1);
            break;

            case SDLK_LEFT:
            velocity.add_x(-1);
            break;

            case SDLK_RIGHT:
            velocity.add_x(1);
            break;
        }
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
