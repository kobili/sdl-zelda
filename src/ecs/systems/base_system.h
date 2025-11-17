#ifndef ECS_BASE_SYSTEM_H
#define ECS_BASE_SYSTEM_H

#include "SDL.h"

#include "../entity.h"


class ECSManager; // forward declaration


class ISystem {
public:
    ISystem(ECSManager* manager) {
        m_ecs = manager;
    };

    virtual ~ISystem() = default;

    void update(Uint32 dt);

    void virtual update_entity(Entity& entity, Uint32 dt) = 0;

protected:
    ECSManager* m_ecs;  // non-owning
};


class IInputSystem {
public:
    IInputSystem(ECSManager* manager) {
        m_ecs = manager;
    }

    virtual ~IInputSystem() = default;

    void handle_input(SDL_Event& e);
    void virtual handle_input_for_entity(SDL_Event& e, Entity& entity) = 0;

protected:
    ECSManager* m_ecs;  // non-owning
};

#endif
