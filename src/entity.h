#ifndef ENTITY_H
#define ENTITY_H

#include "SDL.h"
#include <vector>

#include "sprite_sheet.h"

class Entity {
public:
    Entity();
    ~Entity();
    void free();

    /**
     * Render the Player to the screen.
     * \param scale_x The horizontal scaling factor from level to screen space
     * \param scale_y The vertical scaling factor from level to screen space
     */
    void render(int scale_x, int scale_y);

    void set_sprite_sheet(SpriteSheet* sprite_sheet);

    void set_x(int x);
    void set_y(int y);

    void move(std::vector<SDL_Rect*> colliders);

    SDL_Rect& get_collider();
    void update_collider();

private:
    int x, y;
    int vel_x, vel_y;

    SpriteSheet* m_sprite_sheet;
    SDL_Rect m_collider;
};

#endif
