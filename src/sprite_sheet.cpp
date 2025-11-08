#include "sprite_sheet.h"


SpriteSheet create_sprite_sheet(Texture* texture, int sprite_width_px, int sprite_height_px) {
    SpriteSheet sprite_sheet;
    sprite_sheet.texture = texture;

    sprite_sheet.sprite_width_px = sprite_width_px;
    sprite_sheet.sprite_height_px = sprite_height_px;

    sprite_sheet.cols = texture->w / sprite_width_px;
    sprite_sheet.rows = texture->h / sprite_height_px;

    return sprite_sheet;
}


SDL_Rect get_sprite(SpriteSheet sprite_sheet, int x, int y) {
    SDL_Rect src;
    src.w = sprite_sheet.sprite_width_px;
    src.h = sprite_sheet.sprite_height_px;

    src.x = x * sprite_sheet.sprite_width_px;
    src.y = y * sprite_sheet.sprite_height_px;

    return src;
}


void free_sprite_sheet(SpriteSheet* sprite_sheet) {
    free_texture(sprite_sheet->texture);
    free(sprite_sheet);
}
