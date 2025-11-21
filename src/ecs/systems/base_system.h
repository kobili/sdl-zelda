#ifndef ECS_BASE_SYSTEM_H
#define ECS_BASE_SYSTEM_H

#include "SDL.h"

#include "../../input_manager.h"


class ECSManager; // forward declaration


class ISystem {
public:
    ISystem(ECSManager* manager) {
        m_ecs = manager;
    };

    virtual ~ISystem() = default;

    void update(Uint32 dt);

    void virtual update_entity(Uint32 entity, Uint32 dt) = 0;

protected:
    ECSManager* m_ecs;  // non-owning
};


class IInputSystem : public ISystem {
public:
    IInputSystem(ECSManager* manager, InputManager* input_manager) : ISystem(manager) {
        m_input_manager = input_manager;
    }

protected:
    InputManager* m_input_manager; // non-owning
};

#endif
