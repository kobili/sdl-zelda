#ifndef SWORD_ANIMATION_H
#define SWORD_ANIMATION_H


#include "base_system.h"

#include "../../texture_manager.h"
#include "../../window.h"
#include "../../cameras/camera.h"


class SwordAnimationSystem : public ISystem {
public:
    SwordAnimationSystem(ECSManager* ecs, TextureManager* texture_manager, Camera* camera, Window* window);
    void update_entity(Uint32 entity_id, Uint32 dt) override;

private:
    TextureManager* m_texture_manager; // non-owning
    Camera* m_camera;
    Window* m_window;
};

#endif
