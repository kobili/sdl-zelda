#ifndef HURTBOX_SYSTEM_H
#define HURTBOX_SYSTEM_H

#include "base_system.h"

#include "../../cameras/camera.h"
#include "../../window.h"


class HurtboxIncrementSystem : public ISystem {
public:
    using ISystem::ISystem;
    void update_entity(int entity, Uint32 dt) override;
};


class HurtboxDebugRenderSystem : public ISystem {
public:
    HurtboxDebugRenderSystem(ECSManager* ecs, Camera* camera, Window* window);
    void update_entity(int entity, Uint32 dt) override;

private:
    Camera* m_camera;
    Window* m_window;
};

#endif
