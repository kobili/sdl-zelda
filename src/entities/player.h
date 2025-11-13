#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>

#include "clickable_entity.h"
#include "../utils.h"

#include "../observers/window_observer.h"
#include "../cameras/camera.h"


const int DEFAULT_VELOCITY = 1;


class Player : public ClickableEntity {
public:
    using ClickableEntity::ClickableEntity;

    void handle_event(SDL_Event& e) override;

    void move(std::vector<SDL_Rect*> colliders) override;

    Zone get_current_zone();

private:
    void on_click() override;
};

#endif
