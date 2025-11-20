#ifndef CLICK_SYSTEM_H
#define CLICK_SYSTEM_H

#include "base_system.h"
#include "../../window.h"
#include "../../cameras/camera.h"


class ClickSystem : public IInputSystem {
public:
    ClickSystem(ECSManager* manager, InputManager* input_manager, Window* window, Camera* camera);
    void virtual update_entity(int entity_id, Uint32 dt) override;

private:
    Window* m_window;   // non-owning
    Camera* m_camera;   // non-owning
};

#endif
