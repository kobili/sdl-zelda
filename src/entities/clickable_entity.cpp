#include "clickable_entity.h"


ClickableEntity::ClickableEntity(SpriteSheet* sprite, ObservableWindow* window, Camera* camera) : Entity(sprite) {
    std::unique_ptr<ClickHitbox> _click_hitbox (
        new ClickHitbox(
            m_collider,
            window,
            camera
        )
    );

    click_hitbox = std::move(_click_hitbox);
}


void ClickableEntity::set_x(int x) {
    Entity::set_x(x);
    click_hitbox->update_position(this->x, this->y);
}

void ClickableEntity::set_y(int y) {
    Entity::set_y(y);
    click_hitbox->update_position(this->x, this->y);
}

void ClickableEntity::on_click() {}

void ClickableEntity::handle_event(SDL_Event& e) {
    if (click_hitbox->detect_click(e)) {
        on_click();
    }
}
