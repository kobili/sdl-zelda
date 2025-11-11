#include "./managers.h"


std::unique_ptr<TextureManager> load_textures(Window* window) {
    std::vector<std::string> texture_files = {
        "resources/screen_01.png",
        "resources/link_walk_sprite.png",
        "resources/oktorok_sprites.png",
        "resources/tileset_overworld_forest.png",
        "resources/tileset_overworld_death_mountain.png"
    };

    std::unique_ptr<TextureManager> texture_manager (new TextureManager(window));
    for (int i = 0; i < texture_files.size(); i++) {
        std::string file_path = texture_files[i];
        if (!texture_manager->load_texture(file_path)) {
            printf("failed to load texture: %s. Exiting...\n", file_path.c_str());
            return NULL;
        }
    }

    return texture_manager;
}


std::unique_ptr<SpriteManager> load_sprites(TextureManager* textures) {
    std::vector<std::string> texture_files = {
        "resources/link_walk_sprite.png",
        "resources/oktorok_sprites.png",
    };

    std::unique_ptr<SpriteManager> sprite_manager (new SpriteManager());
    for (int i = 0; i < texture_files.size(); i++) {
        std::string texture_file = texture_files[i];

        Texture* texture = textures->get_texture(texture_file);
        if (!sprite_manager->load_sprite(texture, 16, 16)) {
            printf("failed to load sprite for %s\n", texture_file.c_str());
            return NULL;
        }
    }

    return sprite_manager;
}
