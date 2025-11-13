#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "SDL.h"

class Sprite {
public:
    Sprite(std::string texture_name, int sprite_width_px, int sprite_height_px);

    SDL_Rect get_sprite(int x, int y);
    int get_sprite_width();
    int get_sprite_height();
    std::string get_texture_name();

private:
    std::string m_texture_name;
    int m_sprite_width_px, m_sprite_height_px;

    // int m_rows, m_cols;
};


#endif
