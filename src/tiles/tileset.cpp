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
    SDL_Rect clip = {
        _i,
        _j,
        m_tile_width_px,
        m_tile_height_px
    };

    m_texture->render(x, y, &clip);
}

int Tileset::get_tile_width() {
    return m_tile_width_px;
}


int Tileset::get_tile_height() {
    return m_tile_height_px;
}


void render_screen_01__upper_left(Tileset& tileset) {
    int tile_w = tileset.get_tile_width();
    int tile_h = tileset.get_tile_height();

    // upper left
    for (int i = 0; i < 7; i++) {
        tileset.render_tile(6, 3, i * tile_w, 0);
    }
    for (int i = 0; i < 6; i++) {
        if (i == 4) {
            continue;
        }
        tileset.render_tile(6, 3, i * tile_w, tile_h);
    }
    tileset.render_tile(7, 3, 6 * tile_w, tile_h);
    for (int i = 0; i < 3; i++) {
        tileset.render_tile(6, 3, i * tile_w, 2 * tile_h);
    }
    tileset.render_tile(7, 3, 3 * tile_w, 2 * tile_h);
    for (int i = 0 ; i < 2; i++) {
        tileset.render_tile(6, 3, i * tile_w, 3 * tile_h);
    }
    tileset.render_tile(7, 3, 2 * tile_w, 3 * tile_h);

    tileset.render_tile(6, 3, 0, 4 * tile_h);
    tileset.render_tile(7, 3, tile_w, 4 * tile_h);
}


void render_screen_01__upper_right(Tileset& tileset) {
    int tile_w = tileset.get_tile_width();
    int tile_h = tileset.get_tile_height();

    for (int i = 9; i < 16; i++) {
        for (int j = 0; j < 4; j++) {
            tileset.render_tile(6, 3, i * tile_w, j * tile_h);
        }
    }
    tileset.render_tile(5, 3, 9 * tile_w, 4 * tile_h);
    for (int i = 10; i < 16; i++) {
        tileset.render_tile(6, 3, i * tile_w, 4 * tile_h);
    }
}


void render_screen_01__bottom(Tileset& tileset) {
    int tile_w = tileset.get_tile_width();
    int tile_h = tileset.get_tile_height();

    
    tileset.render_tile(3.5, 3.0, 0, 6 * tile_h);
    tileset.render_tile(4, 3.0, tile_w, 6 * tile_h);

    tileset.render_tile(3.5, 3.0, 15 * tile_w, 6 * tile_h);
    tileset.render_tile(3.5, 3.0, 14 * tile_w, 6 * tile_h);

    for (int i = 0; i < 2; i++) {
        for (int j = 7; j < 10; j++) {
            tileset.render_tile(6, 3, i * tile_w, j * tile_h);
        }
    }
    for (int i = 14; i < 16; i++) {
        for (int j = 7; j < 10; j++) {
            tileset.render_tile(6, 3, i * tile_w, j * tile_h);
        }
    }

    for (int i = 2; i < 14; i++) {
        tileset.render_tile(3.5, 3.0, i * tile_w, 9 * tile_h);
    }
    for (int i = 0; i < 16; i++) {
        tileset.render_tile(6, 3, i * tile_w, 10 * tile_h);
    }
}


void render_screen_01(Tileset& tileset) {
    render_screen_01__upper_left(tileset);
    render_screen_01__upper_right(tileset);
    render_screen_01__bottom(tileset);
}
