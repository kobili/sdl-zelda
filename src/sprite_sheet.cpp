#include "sprite_sheet.h"


SpriteSheet::SpriteSheet() {
    m_texture = NULL;

    m_rows = 0;
    m_cols = 0;

    m_sprite_width_px = 0;
    m_sprite_height_px = 0;
}


bool SpriteSheet::load_sprite_sheet(Texture* texture, int sprite_width_px, int sprite_height_px) {
    m_texture = texture;

    m_sprite_width_px = sprite_width_px;
    m_sprite_height_px = sprite_height_px;

    m_cols = texture->get_width() / sprite_width_px;
    m_rows = texture->get_height() / sprite_height_px;

    return true;
}


bool SpriteSheet::load_sprite_sheet(
    SDL_Renderer* renderer,
    const char* path,
    int sprite_width_px,
    int sprite_height_px
) {
    Texture* texture = new Texture();
    if (!texture->load_texture(renderer, path)) {
        delete texture;
        return false;
    }

    return load_sprite_sheet(texture, sprite_width_px, sprite_height_px);
}


SDL_Rect SpriteSheet::get_sprite(int x, int y) {
    SDL_Rect src;
    src.w = m_sprite_width_px;
    src.h = m_sprite_height_px;

    src.x = x * m_sprite_width_px;
    src.y = y * m_sprite_height_px;

    return src;
}


int SpriteSheet::get_sprite_width() {
    return m_sprite_width_px;
}


int SpriteSheet::get_sprite_height() {
    return m_sprite_height_px;
}


void SpriteSheet::render_sprite(int i, int j, int x, int y) {
    SDL_Rect src = get_sprite(i, j);
    m_texture->render(x, y, &src);
}


Texture* SpriteSheet::get_texture() {
    return m_texture;
}
