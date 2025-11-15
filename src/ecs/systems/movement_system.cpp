#include "movement_system.h"

#include "../components/movement.h"
#include "../components/velocity.h"
#include "../components/position.h"
#include "../components/collider.h"

#include "../../constants.h"


void MovementSystem::update_entity(Entity& entity) {
    Movement* movement = m_ecs->get_component<Movement>(entity);
    if (movement == NULL) {
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

    position.set_x(position.get_x() + velocity.get_x());
    hitbox.x = position.get_x();
    if (
        position.get_x() < 0
        || position.get_x() > OVERWORLD_WIDTH - hitbox.w
    ) {
        position.set_x(position.get_x() - velocity.get_x());
        hitbox.x = position.get_x();
    }

    position.set_y(position.get_y() + velocity.get_y());
    hitbox.y = position.get_y();
    if (
        position.get_y() < 0
        || position.get_y() > OVERWORLD_HEIGHT - hitbox.h
    ) {
        position.set_y(position.get_y() - velocity.get_y());
        hitbox.y = position.get_y();
    }
}
