#include "system_manager.h"


ISystem* SystemManager::register_system(std::unique_ptr<ISystem> system) {
    m_systems.push_back(std::move(system));

    return m_systems[m_systems.size()-1].get();
}


void SystemManager::update(Uint32 dt) {
    // for (const auto& iter : m_systems) {
    //     ISystem& system = *iter.second;
    //     system.update(dt);
    // }

    for (const auto& _system : m_systems) {
        ISystem& system = *_system;
        system.update(dt);
    }
}
