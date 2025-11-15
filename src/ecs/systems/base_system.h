#ifndef ECS_BASE_SYSTEM_H
#define ECS_BASE_SYSTEM_H

#include "../ecs_manager.h"


class ISystem {
public:
    ISystem(ECSManager* manager) {
        m_ecs = manager;
    };

    void virtual update() = 0;

protected:
    ECSManager* m_ecs;  // non-owning
};

#endif
