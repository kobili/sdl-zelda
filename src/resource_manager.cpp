#include "resource_manager.h"


ResourceManager::ResourceManager(Window* window) {
    m_window = window;
    m_renderer = window->get_renderer();
}


bool ResourceManager::load_texture(std::string file_path) {
    std::unique_ptr<Texture> texture (new Texture());
    if (!texture->load_texture(m_renderer, file_path.c_str())) {
        return false;
    }
    texture->start_observing(m_window);

    m_texture_map.insert(std::make_pair(file_path, std::move(texture)));

    printf("loaded texture %s\n", file_path.c_str());

    return true;
}


Texture* ResourceManager::get_texture(std::string file_path) {
    if (m_texture_map.find(file_path) == m_texture_map.end()) {
        return NULL;
    }

    return m_texture_map[file_path].get();
}


bool ResourceManager::load_sprite(std::string texture_name, int sprite_width_px, int sprite_height_px) {
    Texture* texture = get_texture(texture_name);
    if (texture == NULL) {
        printf("Failed to load sprite %s: Texture not loaded\n", texture_name.c_str());
        return false;
    }

    std::unique_ptr<SpriteSheet> sprite_sheet (new SpriteSheet(texture, sprite_width_px, sprite_height_px));

    m_sprite_map.insert(std::make_pair(texture_name, std::move(sprite_sheet)));

    printf("loaded sprite for %s\n", texture_name.c_str());
    return true;
}


SpriteSheet* ResourceManager::get_sprite(std::string texture_name) {
    if (m_sprite_map.find(texture_name) == m_sprite_map.end()) {
        return NULL;
    }

    return m_sprite_map[texture_name].get();
}


bool ResourceManager::load_tileset(std::string texture_name, int tile_width_px, int tile_height_px) {
    Texture* texture = get_texture(texture_name);
    if (texture == NULL) {
        printf("failed to load tileset %s: Texture not loaded\n", texture_name.c_str());
        return false;
    }

    std::unique_ptr<Tileset> tileset (new Tileset(texture, tile_width_px, tile_height_px));
    m_tileset_map.insert(
        std::make_pair(
            texture_name,
            std::move(tileset)
        )
    );

    printf("loaded tileset %s\n", texture_name.c_str());
    return true;
}


Tileset* ResourceManager::get_tileset(std::string texture_name) {
    if (m_tileset_map.find(texture_name) == m_tileset_map.end()) {
        return NULL;
    }
    return m_tileset_map[texture_name].get();
}
