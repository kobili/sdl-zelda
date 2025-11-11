#ifndef TILESET_H
#define TILESET_H

#include "texture.h"


class Tileset {
public:
    Tileset(Texture* texture, int tile_width_px, int tile_height_px);

    /**
     * Render the tile at column `i`, row `j` at coordinates (`x`, `y`) in level space.
     * 
     * Use a half integer step to specify a combination of two tiles.
     * \param i The column of the tileset
     * \param j The row of the tileset
     * \param x The starting x coordinate of where to render the tile in world space
     * \param y The starting y coordinate of where to render the tile in world space
     */
    void render_tile(double i, double j, int x, int y);

    int get_tile_width();
    int get_tile_height();


    
    private:
    int m_tile_width_px, m_tile_height_px;
    
    int n_cols, n_rows;
    Texture* m_texture;  // non-owning
};


void render_screen_01(Tileset& tileset);


#endif
