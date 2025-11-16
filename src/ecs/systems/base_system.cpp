#include "base_system.h"

#include "../managers/ecs_manager.h"

void ISystem::update() {
    for (auto& _entity : m_ecs->get_entities()) {
        Entity& entity = *_entity;
        update_entity(entity);
    }
}


void IInputSystem::handle_input(SDL_Event& e) {
    for (auto& _entity : m_ecs->get_entities()) {
        Entity& entity = *_entity;
        handle_input_for_entity(e, entity);
    }
}
