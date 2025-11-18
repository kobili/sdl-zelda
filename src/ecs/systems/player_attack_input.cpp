#include "player_attack_input.h"

#include "../components/player.h"
#include "../components/movement.h"
#include "../components/velocity.h"
#include "../components/sprite_animation.h"

#include "../managers/ecs_manager.h"


void PlayerAttackInputSystem::handle_input_for_entity(SDL_Event& e, Entity& entity) {
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

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_f:
            velocity.set_x(0);
            velocity.set_y(0);
            animation->stop_animation();
            printf("Attacked\n");
            break;
        }
    }
}
