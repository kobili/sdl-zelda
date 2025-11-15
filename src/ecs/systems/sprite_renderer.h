#ifndef SPRITE_RENDERER_SYSTEM_H
#define SPRITE_RENDERER_SYSTEM_H

#include "base_system.h"

#include "../../texture_manager.h"
#include "../../window.h"
#include "../../cameras/camera.h"


class SpriteRenderSystem : public ISystem  {
public:
    SpriteRenderSystem(ECSManager* ecs, TextureManager* texture_manager, Camera* camera, Window* window);

    void update_entity(Entity& entity) override;

private:
    TextureManager* m_texture_manager;
    Camera* m_camera;
    Window* m_window;
};

#endif
