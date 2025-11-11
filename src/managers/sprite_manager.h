#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <map>
#include <memory>
#include <string>

#include "../sprite_sheet.h"
#include "../texture.h"


class SpriteManager {
public:
    SpriteManager();
    SpriteManager(const SpriteManager&) = delete;
    SpriteManager& operator=(const SpriteManager&) = delete;

    bool load_sprite(Texture* texture, int sprite_width_px, int sprite_height_px);
    SpriteSheet* get_sprite(std::string texture_name);

private:
    std::map< std::string, std::unique_ptr<SpriteSheet> > m_sprite_map;
};

#endif
