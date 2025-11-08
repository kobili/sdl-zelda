#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include "texture.h"


struct SpriteSheet {
    Texture* texture;
    int rows;
    int cols;
    int sprite_width_px;
    int sprite_height_px;
};

SpriteSheet create_sprite_sheet(Texture* texture, int sprite_width_px, int sprite_height_px);
SDL_Rect get_sprite(SpriteSheet sprite_sheet, int x, int y);
void free_sprite_sheet(SpriteSheet* sprite_sheet);

#endif
