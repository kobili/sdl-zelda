#ifndef SPRITE_RENDERER_SYSTEM_H
#define SPRITE_RENDERER_SYSTEM_H

#include "base_system.h"

#include "../../texture_manager.h"
#include "../../window.h"
#include "../../cameras/camera.h"


class CharacterRenderer  {
public:
    CharacterRenderer(ECSManager* ecs, TextureManager* texture_manager, Camera* camera, Window* window);

    void render(int entity, Uint32 dt);

private:
    ECSManager* m_ecs;
    TextureManager* m_texture_manager;
    Camera* m_camera;
    Window* m_window;
};


class PlayerSpriteRenderSystem : public ISystem {
public:
    PlayerSpriteRenderSystem(ECSManager* ecs, TextureManager* texture_manager, Camera* camera, Window* window);

    void update_entity(int entity, Uint32 dt) override;

private:
    CharacterRenderer m_renderer;
};


class EnemySpriteRenderSystem : public ISystem {
public:
    EnemySpriteRenderSystem(ECSManager* ecs, TextureManager* texture_manager, Camera* camera, Window* window);

    void update_entity(int entity, Uint32 dt);

private:
    CharacterRenderer m_renderer;
};

#endif
