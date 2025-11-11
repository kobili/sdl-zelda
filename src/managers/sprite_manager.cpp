#include "sprite_manager.h"


SpriteManager::SpriteManager() {
}


bool SpriteManager::load_sprite(Texture* texture, int sprite_width_px, int sprite_height_px) {
    std::unique_ptr<SpriteSheet> sprite_sheet (new SpriteSheet(texture, sprite_width_px, sprite_height_px));

    m_sprite_map.insert(std::make_pair(texture->get_file_path(), std::move(sprite_sheet)));

    printf("loaded sprite for %s\n", texture->get_file_path().c_str());
    return true;
}


SpriteSheet* SpriteManager::get_sprite(std::string texture_name) {
    if (m_sprite_map.find(texture_name) == m_sprite_map.end()) {
        return NULL;
    }

    return m_sprite_map[texture_name].get();
}
