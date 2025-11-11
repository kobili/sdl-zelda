#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include "texture.h"


class SpriteSheet {
public:
    SpriteSheet();
    SpriteSheet(Texture* texture, int sprite_width_px, int sprite_height_px);

    bool load_sprite_sheet(Texture* texture, int sprite_width_px, int sprite_height_px);
    bool load_sprite_sheet(
        SDL_Renderer* renderer,
        const char* path,
        int sprite_width_px,
        int sprite_height_px
    );

    SDL_Rect get_sprite(int x, int y);
    int get_sprite_width();
    int get_sprite_height();
    Texture* get_texture();

    /**
     * Render the sprite in column `i` row `j` of the sprite sheet at coordinates (`x`, `y`) on the screen.
     * 
     * \param i The column on the sprite sheet of the selected sprite
     * \param j The row on the sprite sheet of the selected sprite
     * \param x The x coordinate in screen space to render the texture
     * \param y The y coordinate in screen space to render the texture
     * \param scale_x The horizontal scaling factor (defaults to 1.0)
     * \param scale_y The vertical scaling factor (defaults to 1.0)
     */
    void render_sprite(int i, int j, int x, int y, double scale_x = 1.0, double scale_y = 1.0);

private:
    Texture* m_texture;  // non-owning reference

    int m_rows, m_cols;
    int m_sprite_width_px, m_sprite_height_px;
};


#endif
