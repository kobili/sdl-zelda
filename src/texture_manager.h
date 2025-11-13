#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <string>
#include <memory>
#include <vector>

#include "SDL.h"

#include "window.h"
#include "texture.h"


class TextureManager {
public:
    TextureManager(Window* window);
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    bool load_texture(std::string file_path);
    Texture* get_texture(std::string file_path);
    bool has_texture(std::string file_path);

private:
    Window* m_window;         // non-owning
    SDL_Renderer* m_renderer; // non-owning
    std::map<std::string, std::unique_ptr<Texture>> m_texture_map;
};


#endif
