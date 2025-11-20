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


void ECSManager::update(Uint32 dt) {
    m_system_manager.update(dt);
}


void ECSManager::remove_entity(int entity_id) {
    m_entities.erase(
        std::remove_if(
            m_entities.begin(),
            m_entities.end(),
            [entity_id](std::unique_ptr<Entity>& entity) {
                return entity->get_id() == entity_id;
            }
        ),
        m_entities.end()
    );

    // remove from set
    for (auto it = m_entity_set.begin(); it != m_entity_set.end();) {
        if (it->get_id() == entity_id) {
            it = m_entity_set.erase(it);
        } else {
            it++;
        }
    }

    m_component_manager.remove_components(entity_id);
}
