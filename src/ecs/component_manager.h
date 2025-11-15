#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <map>
#include <typeindex>
#include <memory>

#include "entity.h"


class ComponentManager {
public:
    template <typename T>
    bool add_component(Entity entity, std::unique_ptr<T> component) {
        std::map<int, std::unique_ptr<T> >& component_map = get_map<T>();
    
        if (component_map.find(entity.get_id()) != component_map.end()) {
            printf("Entity with id %d already has component of type %s\n", entity.get_id(), typeid(T).name());
            return false;
        }

        component_map[entity.get_id()] = std::move(component);

        return true;
    }

    template <typename T>
    T* get_component(Entity entity) {
        std::map<int, std::unique_ptr<T> >& component_map = get_map<T>();

        if (component_map.find(entity.get_id()) == component_map.end()) {
            printf("Entity with id %d has no component of type %s\n", entity.get_id(), typeid(T).name());
            return NULL;
        }

        return component_map[entity.get_id()].get();
    }

private:
    /**
     * Type erased
    ```
    std::unordered_map< std::type_index, std::shared_ptr<std::map<int, std::unique_ptr<T>>>
    ```
     */
    std::unordered_map<std::type_index, std::shared_ptr<void> > m_component_maps;

    template <typename T>
    std::map<int, std::unique_ptr<T> >& get_map() {
        std::type_index type = std::type_index(typeid(T));

        if (m_component_maps.find(type) == m_component_maps.end()) {
            // map doesn't exist; create it
            auto new_map = std::make_shared<std::map<int, std::unique_ptr<T>>>();
            m_component_maps[type] = std::move(new_map);
        }

        return *std::static_pointer_cast< std::map<int, std::unique_ptr<T> > >(m_component_maps[type]);
    }
};


#endif
