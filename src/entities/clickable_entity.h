#ifndef CLICKABLE_ENTITY_H
#define CLICKABLE_ENTITY_H

#include "entity.h"
#include "../clickable.h"


class ClickableEntity : public Entity {
public:
    ClickableEntity(SpriteSheet* sprite, ObservableWindow* window, Camera* camera);
    void set_x(int x) override;
    void set_y(int y) override;

    void virtual handle_event(SDL_Event& e);

protected:
    std::unique_ptr<ClickHitbox> click_hitbox;

    void virtual on_click();
};

#endif
