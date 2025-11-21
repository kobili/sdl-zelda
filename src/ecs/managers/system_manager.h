#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <map>
#include <memory>

#include "SDL.h"

#include "../systems/base_system.h"


class SystemManager {
public:
    ISystem* register_system(std::unique_ptr<ISystem> system);

    void update(Uint32 dt);

private:
    std::vector<std::unique_ptr<ISystem>> m_systems;
};

#endif
