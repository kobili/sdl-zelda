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
