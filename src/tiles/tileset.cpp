#include "tileset.h"

#include "SDL.h"


Tileset::Tileset(Texture* texture, int tile_width_px, int tile_height_px) {
    m_texture = texture;

    m_tile_width_px = tile_width_px;
    m_tile_height_px = tile_height_px;

    n_cols = texture->get_width() / tile_width_px;
    n_rows = texture->get_height() / tile_height_px;
}

void Tileset::render_tile(double i, double j, int x, int y) {
    int _i = i * (double) m_tile_width_px;
    int _j = j * (double) m_tile_height_px;
    SDL_Rect clip = {_i, _j, m_tile_width_px, m_tile_height_px};

    m_texture->render(x, y, &clip);
}

int Tileset::get_tile_width() {
    return m_tile_width_px;
}


int Tileset::get_tile_height() {
    return m_tile_height_px;
}
