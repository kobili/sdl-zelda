#include "system_manager.h"


ISystem* SystemManager::register_system(std::unique_ptr<ISystem> system, int priority) {
    if (m_systems.find(priority) != m_systems.end()) {
        printf("System with priority %d is already registered\n", priority);
        return NULL;
    }

    m_systems[priority] = std::move(system);

    return m_systems[priority].get();
}

IInputSystem* SystemManager::register_system(std::unique_ptr<IInputSystem> system, int priority) {
    if (m_input_systems.find(priority) != m_input_systems.end()) {
        printf("Input system with priority %d is already registered\n", priority);
        return NULL;
    }

    m_input_systems[priority] = std::move(system);

    return m_input_systems[priority].get();
}


void SystemManager::handle_input(SDL_Event& e) {
    for (const auto& iter : m_input_systems) {
        IInputSystem& system = *iter.second;
        system.handle_input(e);
    }
}


void SystemManager::update(Uint32 dt) {
    for (const auto& iter : m_systems) {
        ISystem& system = *iter.second;
        system.update(dt);
    }
}
