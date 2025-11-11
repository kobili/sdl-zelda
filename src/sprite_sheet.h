#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include "texture.h"


class SpriteSheet {
public:
    SpriteSheet();
    ~SpriteSheet();

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

    void free();

    void render_sprite(int i, int j, int x, int y);

private:
    Texture* m_texture;

    int m_rows, m_cols;
    int m_sprite_width_px, m_sprite_height_px;
};


#endif
