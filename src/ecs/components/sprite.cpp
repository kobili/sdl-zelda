#include "sprite.h"


Sprite::Sprite(std::string texture_name, int sprite_width_px, int sprite_height_px) {
    m_texture_name = texture_name;
    m_sprite_width_px = sprite_width_px;
    m_sprite_height_px = sprite_height_px;
}


SDL_Rect Sprite::get_sprite(int x, int y) {
    SDL_Rect src;
    src.w = m_sprite_width_px;
    src.h = m_sprite_height_px;

    src.x = x * m_sprite_width_px;
    src.y = y * m_sprite_height_px;

    return src;
}


int Sprite::get_sprite_width() {
    return m_sprite_width_px;
}


int Sprite::get_sprite_height() {
    return m_sprite_height_px;
}


std::string Sprite::get_texture_name() {
    return m_texture_name;
}
