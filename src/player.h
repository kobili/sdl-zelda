#ifndef PLAYER_H
#define PLAYER_H

#include "sprite_sheet.h"
#include <vector>


const int DEFAULT_VELOCITY = 2;


class Player {
public:
    Player();
    int get_x();
    int get_y();

    void set_sprite_sheet(SpriteSheet* sprite_sheet);

    /**
     * Render the Player to the screen.
     * \param scale_x The horizontal scaling factor from level to screen space
     * \param scale_y The vertical scaling factor from level to screen space
     */
    void render(int scale_x, int scale_y);

    void handle_event(SDL_Event& e);

    void move(std::vector<SDL_Rect*> colliders);

    SDL_Rect& get_collider();

    /**
     * Reposition the collider so that it lines up with the player's position
     */
    void update_collider();

private:
    // position in level space; NOT screen space
    int x, y;
    int vel_x, vel_y;
    SpriteSheet* m_sprite_sheet;

    SDL_Rect collider;
};

#endif
