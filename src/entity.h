#ifndef ENTITY_H
#define ENTITY_H

#include "SDL.h"
#include <vector>

#include "sprite_sheet.h"
#include "camera.h"

class Entity {
public:
    Entity();
    Entity(SpriteSheet* sprite_sheet);

    void render(Camera& camera);

    void set_sprite_sheet(SpriteSheet* sprite_sheet);

    int get_x();
    int get_y();

    void set_x(int x);
    void set_y(int y);

    void virtual move(std::vector<SDL_Rect*> colliders);

    SDL_Rect& get_collider();
    void update_collider();

protected:
    int x, y;
    int vel_x, vel_y;

    SpriteSheet* m_sprite_sheet;  // non-owning reference
    SDL_Rect m_collider;
};

#endif
