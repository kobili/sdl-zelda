#include "movement_system.h"

#include <vector>

#include "../components/movement.h"
#include "../components/velocity.h"
#include "../components/position.h"
#include "../components/collider.h"
#include "../components/character.h"
#include "../managers/ecs_manager.h"

#include "../../constants.h"
#include "../../utils.h"


void MovementSystem::update_entity(Entity& entity, Uint32 dt) {
    Movement* movement = m_ecs->get_component<Movement>(entity);
    if (movement == NULL) {
        return;
    }

    Character* character = m_ecs->get_component<Character>(entity);
    if (character!= NULL && character->get_character_state() == CharacterState::ATTACKING) {
        printf("attacking... skipping movement...\n");
        // don't move while the character is attacking
        return;
    }

    Velocity* _velocity = m_ecs->get_component<Velocity>(entity);
    if (_velocity == NULL) {
        return;
    }
    Velocity& velocity = *_velocity;

    Position* _position = m_ecs->get_component<Position>(entity);
    if (_position == NULL) {
        return;
    }
    Position& position = *_position;


    // handle collisions
    Collider* _collider = m_ecs->get_component<Collider>(entity);
    if (_collider == NULL) {
        return;
    }
    Collider& collider = *_collider;

    SDL_Rect& hitbox = collider.get_hitbox();

    auto colliders = get_other_colliders(entity);

    position.set_x(position.get_x() + velocity.get_x());
    hitbox.x = position.get_x();
    if (
        position.get_x() < 0
        || position.get_x() > OVERWORLD_WIDTH - hitbox.w
        || check_collisions(hitbox, colliders)
    ) {
        position.set_x(position.get_x() - velocity.get_x());
        hitbox.x = position.get_x();
    }

    position.set_y(position.get_y() + velocity.get_y());
    hitbox.y = position.get_y();
    if (
        position.get_y() < 0
        || position.get_y() > OVERWORLD_HEIGHT - hitbox.h
        || check_collisions(hitbox, colliders)
    ) {
        position.set_y(position.get_y() - velocity.get_y());
        hitbox.y = position.get_y();
    }
}


std::vector<SDL_Rect*> MovementSystem::get_other_colliders(Entity& entity) {
    std::vector<SDL_Rect*> colliders;
    for (auto& _entity : m_ecs->get_entities()) {
        Entity& other_entity = *_entity;
        
        if (other_entity == entity) {
            continue;
        }

        Collider* collider = m_ecs->get_component<Collider>(other_entity);
        if (collider == NULL) {
            continue;
        }

        // this might be a good spot to add extra filtering logic
        colliders.push_back(&collider->get_hitbox());
    }

    return colliders;
}
