#include "player_input.h"

#include "../entity.h"
#include "../components/player.h"
#include "../components/movement.h"
#include "../components/velocity.h"


void PlayerInputSystem::handle_input(SDL_Event& e) {
    for (auto& _entity : m_ecs->get_entities()) {
        Entity& entity = *_entity;

        Player* player = m_ecs->get_component<Player>(entity);
        if (player == NULL) {
            continue;
        }

        Movement* movement = m_ecs->get_component<Movement>(entity);
        if (movement == NULL) {
            continue;
        }

        Velocity* _velocity = m_ecs->get_component<Velocity>(entity);
        if (_velocity == NULL) {
            continue;
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
}
