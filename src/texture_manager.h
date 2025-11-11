#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <string>
#include <memory>

#include "texture.h"
#include "window.h"

/**
 * The source of truth for all loaded textures.
 */
class TextureManager {
public:
    TextureManager(Window* window);
    ~TextureManager();

    TextureManager(const TextureManager&) = delete; // Disable copy constructor
    TextureManager& operator=(const TextureManager&) = delete; // Disable copy assignment operator

    bool load_texture(std::string file_path);
    Texture* get_texture(std::string file_path);

private:
    std::map<std::string, std::unique_ptr<Texture>> m_texture_map;

    Window* m_window;   // non-owning pointer
    SDL_Renderer* m_renderer;  // non-owning pointer
};

#endif
