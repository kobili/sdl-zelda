#include "ecs_manager.h"


ECSManager::ECSManager() {
    next_available_id = 0;
}


bool ECSManager::add_entity(Uint32 entity_id) {
    if (m_entity_set.find(entity_id) != m_entity_set.end()) {
        printf("Entity %d already registered\n", entity_id);
        return false;
    }

    m_entity_set.insert(entity_id);
    return true;
}

const std::unordered_set<Uint32>& ECSManager::get_entities() const {
    return m_entity_set;
}


ISystem* ECSManager::register_system(std::unique_ptr<ISystem> system) {
    return m_system_manager.register_system(std::move(system));
}


void ECSManager::update(Uint32 dt) {
    m_system_manager.update(dt);
}


void ECSManager::remove_entity(Uint32 entity_id) {
    // remove from set
    for (auto it = m_entity_set.begin(); it != m_entity_set.end();) {
        if (*it == entity_id) {
            it = m_entity_set.erase(it);
        } else {
            it++;
        }
    }

    m_component_manager.remove_components(entity_id);
}


void ECSManager::mark_remove(Uint32 entity_id) {
    m_entity_removal_queue.push_back(entity_id);
}


void ECSManager::mark_remove(ComponentRemovalQueueItem component) {
    m_component_removal_queue.push_back(component);
}


void ECSManager::prune_inactive_entities() {
    for (Uint32 id : m_entity_removal_queue) {
        remove_entity(id);
    }
    m_entity_removal_queue.clear();
}


void ECSManager::prune_inactive_components() {
    for (ComponentRemovalQueueItem component_removal : m_component_removal_queue) {
        remove_component(component_removal);
    }
}


void ECSManager::remove_component(ComponentRemovalQueueItem component) {
    m_component_manager.remove_component(component.entity, component.component_type);
}


void ECSManager::add_operation(std::function<void()> operation) {
    m_operations_queue.push_back(operation);
}


void ECSManager::run_operations() {
    for (std::function<void()> op : m_operations_queue) {
        op();
    }

    m_operations_queue.clear();
}


Uint32 ECSManager::create_entity_id() {
    Uint32 id = next_available_id;
    next_available_id++;
    return id;
}
