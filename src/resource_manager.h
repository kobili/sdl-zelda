#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <memory>
#include <vector>


#include "sprite_sheet.h"
#include "texture.h"
#include "tiles/tileset.h"

#include "window.h"


class ResourceManager {
public:
    ResourceManager(Window* window);
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    bool load_texture(std::string file_path);
    Texture* get_texture(std::string file_path);

    bool load_sprite(Texture* texture, int sprite_width_px, int sprite_height_px);
    SpriteSheet* get_sprite(std::string texture_name);

    bool load_tileset(std::string texture_name, int tile_width_px, int tile_height_px);
    Tileset* get_tileset(std::string texture_name);

private:
    std::map<std::string, std::unique_ptr<Texture>> m_texture_map;
    std::map<std::string, std::unique_ptr<SpriteSheet>> m_sprite_map;
    std::map<std::string, std::unique_ptr<Tileset>> m_tileset_map;

    Window* m_window;   // non-owning pointer
    SDL_Renderer* m_renderer;  // non-owning pointer
};

bool load_resources(ResourceManager* manager);

#endif
