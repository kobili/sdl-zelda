#include "texture_manager.h"


TextureManager::TextureManager(Window* window) {
    m_window = window;
    m_renderer = window->get_renderer();
}


TextureManager::~TextureManager() {
}


bool TextureManager::load_texture(std::string file_path) {
    std::unique_ptr<Texture> texture (new Texture());
    if (!texture->load_texture(m_renderer, file_path.c_str())) {
        return false;
    }
    texture->start_observing(m_window);

    m_texture_map.insert(std::make_pair(file_path, std::move(texture)));

    printf("loaded texture %s\n", file_path.c_str());

    return true;
}


Texture* TextureManager::get_texture(std::string file_path) {
    if (m_texture_map.find(file_path) == m_texture_map.end()) {
        return NULL;
    }

    return m_texture_map[file_path].get();
}
