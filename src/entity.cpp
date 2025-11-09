#include "entity.h"


Entity::Entity() {
    x = 0;
    y = 0;
    vel_x = 0;
    vel_y = 0;

    m_sprite_sheet = NULL;

    m_collider.x = 0;
    m_collider.y = 0;
}

Entity::~Entity() {
    free();
    printf("destroyed entity\n");
}

void Entity::free() {
    delete m_sprite_sheet;
    m_sprite_sheet = NULL;
}

void Entity::render(int scale_x, int scale_y) {
    // TODO: add a check for a null sprite sheet
    m_sprite_sheet->render_sprite(
        0,
        0,
        x * scale_x,
        y * scale_y,
        scale_x,
        scale_y
    );
}

void Entity::set_sprite_sheet(SpriteSheet* sprite_sheet) {
    m_sprite_sheet = sprite_sheet;
    m_collider.w = sprite_sheet->get_sprite_width();
    m_collider.h = sprite_sheet->get_sprite_height();
}

void Entity::set_x(int x) {
    this->x = x;
    update_collider();
}

void Entity::set_y(int y) {
    this->y = y;
    update_collider();
}

void Entity::move(std::vector<SDL_Rect*> colliders) {
    // stub
    update_collider();
}

SDL_Rect& Entity::get_collider() {
    return m_collider;
}

void Entity::update_collider() {
    m_collider.x = x;
    m_collider.y = y;
}

