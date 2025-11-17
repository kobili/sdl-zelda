#include "ecs_manager.h"


Entity* ECSManager::add_entity(std::unique_ptr<Entity> entity) {
    if (m_entity_set.find(*entity.get()) != m_entity_set.end()) {
        printf("Entity %d already registered\n", entity->get_id());
        return NULL;
    }

    m_entity_set.insert(*entity.get());

    Entity* retval = entity.get();

    m_entities.push_back(std::move(entity));

    return retval;
}

const std::vector<std::unique_ptr<Entity>>& ECSManager::get_entities() const {
    return m_entities;
}


ISystem* ECSManager::register_system(std::unique_ptr<ISystem> system, int priority) {
    return m_system_manager.register_system(std::move(system), priority);
}


IInputSystem* ECSManager::register_system(std::unique_ptr<IInputSystem> system, int priority) {
    return m_system_manager.register_system(std::move(system), priority);
}


void ECSManager::handle_input(SDL_Event& e) {
    m_system_manager.handle_input(e);
}


void ECSManager::update(Uint32 dt) {
    m_system_manager.update(dt);
}
