#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <map>
#include <typeindex>
#include <memory>

#include "SDL.h"


class IComponentStore {
public:
    virtual ~IComponentStore() = default;
    virtual void remove_component(Uint32 entity_id) = 0;
};


template <typename T>
class ComponentStore : public IComponentStore {
public:
    T* add_component(Uint32 entity_id, T component) {
        m_components[entity_id] = std::unique_ptr<T>(new T(std::move(component)));
        return m_components[entity_id].get();
    }

    T* get_component(Uint32 entity_id) {
        if (m_components.find(entity_id) == m_components.end()) {
            return NULL;
        }

        return m_components[entity_id].get();
    }

    void remove_component(Uint32 entity_id) override {
        m_components.erase(entity_id);
    }
private:
    std::unordered_map<Uint32, std::unique_ptr<T>> m_components;
};


class ComponentManager {
public:
    template <typename T>
    T* add_component(Uint32 entity_id, T component) {
        ComponentStore<T>& component_store = get_or_create_store<T>();
        component_store.add_component(entity_id, component);

        return component_store.get_component(entity_id);
    }

    template <typename T>
    T* get_component(Uint32 entity_id) {
        ComponentStore<T>& component_store = get_or_create_store<T>();

        return component_store.get_component(entity_id);
    }

    void remove_components(Uint32 entity_id) {
        for (auto& pair : m_stores) {
            pair.second->remove_component(entity_id);
        }
    }

    void remove_component(Uint32 entity, std::type_index component_type);

private:
    std::unordered_map<std::type_index, std::unique_ptr<IComponentStore>> m_stores;

    template <typename T>
    ComponentStore<T>& get_or_create_store() {
        std::type_index type = std::type_index(typeid(T));

        if (m_stores.find(type) == m_stores.end()) {
            std::unique_ptr<ComponentStore<T>> store (new ComponentStore<T>());
            ComponentStore<T>* store_ptr = store.get();
            m_stores[type] = std::move(store);

            return *store_ptr;
        }

        return *static_cast<ComponentStore<T>*>(m_stores[type].get());
    }
};


#endif
