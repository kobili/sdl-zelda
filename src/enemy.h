#ifndef ENEMY_H
#define ENEMY_H

#include "sprite_sheet.h"

class Enemy {
public:
    Enemy();

    /**
     * Render the Player to the screen.
     * \param scale_x The horizontal scaling factor from level to screen space
     * \param scale_y The vertical scaling factor from level to screen space
     */
    void render(int scale_x, int scale_y);

    void set_sprite_sheet(SpriteSheet* sprite_sheet);

    void set_x(int x);
    void set_y(int y);

    void move();

private:
    int x, y;
    int vel_x, vel_y;

    SpriteSheet* sprite_sheet;
};


#endif
