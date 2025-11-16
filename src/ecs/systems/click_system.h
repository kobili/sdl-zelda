#ifndef CLICK_SYSTEM_H
#define CLICK_SYSTEM_H

#include "base_system.h"
#include "../../window.h"
#include "../../cameras/camera.h"


class ClickSystem : public IInputSystem {
public:
    ClickSystem(ECSManager* manager, Window* window, Camera* camera);
    void handle_input_for_entity(SDL_Event& e, Entity& entity) override;

private:
    Window* m_window;   // non-owning
    Camera* m_camera;   // non-owning
};

#endif
