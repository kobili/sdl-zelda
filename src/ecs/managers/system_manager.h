#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <map>
#include <memory>

#include "SDL.h"

#include "../systems/base_system.h"


class SystemManager {
public:
    ISystem* register_system(std::unique_ptr<ISystem> system, int priority);
    IInputSystem* register_system(std::unique_ptr<IInputSystem> system, int priority);

    void handle_input(SDL_Event& e);
    void update(Uint32 dt);

private:
    std::map<int, std::unique_ptr<ISystem>> m_systems;
    std::map<int, std::unique_ptr<IInputSystem>> m_input_systems;
};

#endif
