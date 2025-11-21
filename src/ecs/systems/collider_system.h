#ifndef COLLIDER_SYSTEM_H
#define COLLIDER_SYSTEM_H

#include "base_system.h"

#include "../components/collider.h"
#include "../components/hurtbox.h"

#include "../../cameras/camera.h"
#include "../../window.h"
#include "../../texture.h"


class ColliderDebugRenderSystem : public ISystem {
public:
    ColliderDebugRenderSystem(ECSManager* ecs, Camera* camera, Window* window);
    void update_entity(int entity, Uint32 dt) override;

private:
    Camera* m_camera;
    Window* m_window;

    void render_collider(Collider collider);
    void render_hurtbox(Collider collider, Hurtbox hurtbox);
    void render_rectangle(SDL_Rect rect, RGB colour, Uint8 alpha);
};

#endif
