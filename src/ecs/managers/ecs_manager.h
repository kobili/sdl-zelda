#ifndef ECS_MANAGER_H
#define ECS_MANAGER_H


#include <map>
#include <memory>
#include <vector>
#include <unordered_set>
#include <typeindex>

#include "component_manager.h"
#include "system_manager.h" // might cause a circular dependency


struct ComponentRemovalQueueItem {
    Uint32 entity;
    std::type_index component_type;
};


class ECSManager {
public:
    ECSManager();

    bool add_entity(Uint32 entity_id);

    const std::unordered_set<Uint32>& get_entities() const;

    
    void mark_remove(Uint32 entity_id);
    void mark_remove(ComponentRemovalQueueItem component);

    void remove_entity(Uint32 entity_id);
    void remove_component(ComponentRemovalQueueItem component);

    void prune_inactive_entities();
    void prune_inactive_components();

    /**
     * Return the next available id and increment the counter
     */
    Uint32 create_entity_id();

    template <typename T>
    T* add_component(int entity_id, T component) {
        if (m_entity_set.find(entity_id) == m_entity_set.end()) {
            printf("can't add %s for unregistered Entity with id %d\n", typeid(T).name(), entity_id);
            return NULL;
        }

        return m_component_manager.add_component(entity_id, component);
    }

    template <typename T>
    T* get_component(int entity_id) {
        return m_component_manager.get_component<T>(entity_id);
    }

    ISystem* register_system(std::unique_ptr<ISystem> system);

    void update(Uint32 dt);

    void add_operation(std::function<void()> operation);
    void run_operations();

private:
    Uint32 next_available_id;

    ComponentManager m_component_manager;

    SystemManager m_system_manager;

    // for deduplication
    std::unordered_set<Uint32> m_entity_set;

    // entity ids marked to be removed
    std::vector<Uint32> m_entity_removal_queue;
    std::vector<ComponentRemovalQueueItem> m_component_removal_queue;

    std::vector<std::function<void()>> m_operations_queue;
};

#endif
