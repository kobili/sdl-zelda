#ifndef ECS_MANAGER_H
#define ECS_MANAGER_H


#include <map>
#include <memory>
#include <vector>
#include <unordered_set>
#include <typeindex>

#include "component_manager.h"
#include "system_manager.h" // might cause a circular dependency


class ECSManager {
public:
    bool add_entity(int entity_id);

    const std::unordered_set<int>& get_entities() const;

    void remove_entity(int entity_id);

    void mark_remove(int entity_id);

    void prune_inactive_entities();

    template <typename T>
    T* add_component(int entity_id, std::unique_ptr<T> component) {
        if (m_entity_set.find(entity_id) == m_entity_set.end()) {
            printf("can't add %s for unregistered Entity with id %d\n", typeid(T).name(), entity_id);
            return NULL;
        }

        return m_component_manager.add_component(entity_id, std::move(component));
    }

    template <typename T>
    T* get_component(int entity_id) {
        return m_component_manager.get_component<T>(entity_id);
    }

    ISystem* register_system(std::unique_ptr<ISystem> system, int priority);

    void update(Uint32 dt);

private:
    ComponentManager m_component_manager;

    SystemManager m_system_manager;

    // std::vector<std::unique_ptr<Entity>> m_entities;

    // for deduplication
    std::unordered_set<int> m_entity_set;

    // entity ids marked to be removed
    std::vector<int> m_removal_queue;
};

#endif
