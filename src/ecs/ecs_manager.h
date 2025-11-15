#ifndef ECS_MANAGER_H
#define ECS_MANAGER_H


#include <map>
#include <memory>

#include "entity.h"
#include "component_manager.h"


class ECSManager {
public:
    template <typename T>
    bool add_component(Entity e, std::unique_ptr<T> component) {
        return m_component_manager.add_component(e, std::move(component));
    }

    template <typename T>
    T* get_component(Entity e) {
        return m_component_manager.get_component<T>(e);
    }

private:
    ComponentManager m_component_manager;
};

#endif
