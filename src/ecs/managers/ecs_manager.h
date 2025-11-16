#ifndef ECS_MANAGER_H
#define ECS_MANAGER_H


#include <map>
#include <memory>
#include <vector>
#include <unordered_set>
#include <typeindex>

#include "../entity.h"
#include "component_manager.h"
#include "system_manager.h" // might cause a circular dependency


class ECSManager {
public:
    Entity* add_entity(std::unique_ptr<Entity> entity);

    const std::vector<std::unique_ptr<Entity>>& get_entities() const;

    template <typename T>
    T* add_component(Entity entity, std::unique_ptr<T> component) {
        if (m_entity_set.find(entity) == m_entity_set.end()) {
            printf("can't add %s for unregistered Entity with id %d\n", typeid(T).name(), entity.get_id());
            return NULL;
        }

        return m_component_manager.add_component(entity, std::move(component));
    }

    template <typename T>
    T* get_component(Entity entity) {
        return m_component_manager.get_component<T>(entity);
    }

    ISystem* register_system(std::unique_ptr<ISystem> system, int priority);
    IInputSystem* register_system(std::unique_ptr<IInputSystem> system, int priority);

    void handle_input(SDL_Event& e);
    void update();

private:
    ComponentManager m_component_manager;

    SystemManager m_system_manager;

    std::vector<std::unique_ptr<Entity>> m_entities;

    // for deduplication
    std::unordered_set<Entity> m_entity_set;
};

#endif
