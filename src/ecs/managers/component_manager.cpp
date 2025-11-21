#include "component_manager.h"


void ComponentManager::remove_component(Uint32 entity, std::type_index component_type) {
    if (m_stores.find(component_type) == m_stores.end()) {
        return;
    }
    IComponentStore& store = *m_stores[component_type].get();
    store.remove_component(entity);
}
