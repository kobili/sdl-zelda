#include "player_attack_input.h"

#include "../components/player.h"
#include "../components/movement.h"
#include "../components/velocity.h"
#include "../components/sprite_animation.h"

#include "../managers/ecs_manager.h"


void PlayerAttackInputSystem::update_entity(Entity& entity, Uint32 dt) {
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

    auto key_presses = m_input_manager->get_keyboard_events();
    auto key_binds = m_input_manager->get_keybinds();

    for (auto& key_press : key_presses) {
        if (key_press.key_code != key_binds[Action::ATTACK]) {
            continue;
        }
        if (key_press.type != KeyboardEventType::BUTTONDOWN) {
            continue;
        }

        velocity.set_x(0);
        velocity.set_y(0);
        animation->stop_animation();
        printf("Attacked\n");
    }
}
