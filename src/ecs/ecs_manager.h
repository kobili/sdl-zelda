#ifndef ECS_MANAGER_H
#define ECS_MANAGER_H


#include <map>
#include <memory>
#include <vector>
#include <unordered_set>

#include "entity.h"
#include "component_manager.h"


class ECSManager {
public:
    Entity* add_entity(std::unique_ptr<Entity> entity);

    template <typename T>
    bool add_component(Entity entity, std::unique_ptr<T> component) {
        return m_component_manager.add_component(entity, std::move(component));
    }

    template <typename T>
    T* get_component(Entity entity) {
        return m_component_manager.get_component<T>(entity);
    }

private:
    ComponentManager m_component_manager;
    std::vector<std::unique_ptr<Entity>> m_entities;

    // for deduplication
    std::unordered_set<Entity> m_entity_set;
};

#endif
