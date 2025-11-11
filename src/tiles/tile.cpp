#include "tile.h"


Tile::Tile(Tileset* tileset, double i, double j, int x, int y) {
    m_tileset = tileset;

    m_i = i;
    m_j = j;

    level_x = x;
    level_y = y;
}

void Tile::render() {
    m_tileset->render_tile(m_i, m_j, level_x, level_y);
}


std::vector<Tile> render_screen_01__upper_left(Tileset* tileset) {
    std::vector<Tile> tiles;

    int tile_w = tileset->get_tile_width();
    int tile_h = tileset->get_tile_height();

    // upper left
    for (int i = 0; i < 7; i++) {
        tiles.push_back(Tile(tileset, 6, 3, i * tile_w, 0));
    }
    for (int i = 0; i < 6; i++) {
        if (i == 4) {
            continue;
        }
        tiles.push_back(Tile(tileset, 6, 3, i * tile_w, tile_h));
    }
    tiles.push_back(Tile(tileset, 7, 3, 6 * tile_w, tile_h));
    for (int i = 0; i < 3; i++) {
        tiles.push_back(Tile(tileset, 6, 3, i * tile_w, 2 * tile_h));
    }
    tiles.push_back(Tile(tileset, 7, 3, 3 * tile_w, 2 * tile_h));
    for (int i = 0 ; i < 2; i++) {
        tiles.push_back(Tile(tileset, 6, 3, i * tile_w, 3 * tile_h));
    }
    tiles.push_back(Tile(tileset, 7, 3, 2 * tile_w, 3 * tile_h));

    tiles.push_back(Tile(tileset, 6, 3, 0, 4 * tile_h));
    tiles.push_back(Tile(tileset, 7, 3, tile_w, 4 * tile_h));

    return tiles;
}


std::vector<Tile> render_screen_01__upper_right(Tileset* tileset) {
    std::vector<Tile> tiles;

    int tile_w = tileset->get_tile_width();
    int tile_h = tileset->get_tile_height();

    for (int i = 9; i < 16; i++) {
        for (int j = 0; j < 4; j++) {
            tiles.push_back(Tile(tileset, 6, 3, i * tile_w, j * tile_h));
        }
    }
    tiles.push_back(Tile(tileset, 5, 3, 9 * tile_w, 4 * tile_h));
    for (int i = 10; i < 16; i++) {
        tiles.push_back(Tile(tileset, 6, 3, i * tile_w, 4 * tile_h));
    }

    return tiles;
}


std::vector<Tile> render_screen_01__bottom(Tileset* tileset) {
    std::vector<Tile> tiles;

    int tile_w = tileset->get_tile_width();
    int tile_h = tileset->get_tile_height();

    
    tiles.push_back(Tile(tileset, 3.5, 3.0, 0, 6 * tile_h));
    tiles.push_back(Tile(tileset, 4, 3.0, tile_w, 6 * tile_h));

    tiles.push_back(Tile(tileset, 3.5, 3.0, 15 * tile_w, 6 * tile_h));
    tiles.push_back(Tile(tileset, 3.5, 3.0, 14 * tile_w, 6 * tile_h));

    for (int i = 0; i < 2; i++) {
        for (int j = 7; j < 10; j++) {
            tiles.push_back(Tile(tileset, 6, 3, i * tile_w, j * tile_h));
        }
    }
    for (int i = 14; i < 16; i++) {
        for (int j = 7; j < 10; j++) {
            tiles.push_back(Tile(tileset, 6, 3, i * tile_w, j * tile_h));
        }
    }

    for (int i = 2; i < 14; i++) {
        tiles.push_back(Tile(tileset, 3.5, 3.0, i * tile_w, 9 * tile_h));
    }
    for (int i = 0; i < 16; i++) {
        tiles.push_back(Tile(tileset, 6, 3, i * tile_w, 10 * tile_h));
    }

    return tiles;
}


std::vector<Tile> get_screen_1_tiles(Tileset* tileset) {
    std::vector<Tile> tiles;
    auto v1 = render_screen_01__upper_left(tileset);
    auto v2 = render_screen_01__upper_right(tileset);
    auto v3 = render_screen_01__bottom(tileset);

    tiles.insert(tiles.end(), v1.begin(), v1.end());
    tiles.insert(tiles.end(), v2.begin(), v2.end());
    tiles.insert(tiles.end(), v3.begin(), v3.end());

    return tiles;
}
