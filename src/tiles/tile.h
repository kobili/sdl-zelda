#ifndef TILE_H
#define TILE_H

#include "tileset.h"


class Tile {
public:
    Tile(Tileset* tileset, double i, double j, int x, int y);

    void render();

private:
    Tileset* m_tileset;  // non-owning

    double m_i, m_j;

    int level_x, level_y;
};

#endif
