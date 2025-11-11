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



bool load_textures(ResourceManager* manager) {
    std::vector<std::string> texture_files = {
        "resources/screen_01.png",
        "resources/sprites/link.png",
        "resources/sprites/oktorok__red.png",
        "resources/tilesets/overworld__forest.png",
        "resources/tilesets/overworld__death_mountain.png"
    };

    for (int i = 0; i < texture_files.size(); i++) {
        std::string file_path = texture_files[i];
        if (!manager->load_texture(file_path)) {
            printf("failed to load texture: %s. Exiting...\n", file_path.c_str());
            return false;
        }
    }

    return true;
}


bool load_sprites(ResourceManager* manager) {
    std::vector<std::string> texture_files = {
        "resources/sprites/link.png",
        "resources/sprites/oktorok__red.png",
    };

    for (int i = 0; i < texture_files.size(); i++) {
        std::string texture_file = texture_files[i];

        if (!manager->load_sprite(texture_file, 16, 16)) {
            printf("failed to load sprite for %s\n", texture_file.c_str());
            return false;
        }
    }

    return true;
}


bool load_tilesets(ResourceManager* manager) {
    std::vector<std::string> texture_files = {
        "resources/tilesets/overworld__forest.png",
        "resources/tilesets/overworld__death_mountain.png"
    };

    for (int i = 0; i < texture_files.size(); i++) {
        auto texture_file = texture_files[i];
        if (!manager->load_tileset(texture_file, 16, 16)) {
            printf("failed to load tileset %s\n", texture_file.c_str());
            return false;
        }
    }

    return true;
}


bool load_resources(ResourceManager* manager) {
    if (!load_textures(manager)) {
        return false;
    }

    if (!load_sprites(manager)) {
        return false;
    }

    if (!load_tilesets(manager)) {
        return false;
    }

    return true;
}
