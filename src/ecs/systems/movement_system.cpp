#include "movement_system.h"

#include "../components/movement.h"
#include "../components/velocity.h"
#include "../components/position.h"


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

    position.set_x(position.get_x() + velocity.get_x());
    position.set_y(position.get_y() + velocity.get_y());
}
