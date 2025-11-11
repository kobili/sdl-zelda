#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"
#include <string>
#include "window_observer.h"


class Texture {
public:
    Texture();
    ~Texture();

    void free();
    bool load_texture(SDL_Renderer* renderer, const char* path);

    /**
    * Render the texture at x, y in the world. The position will be scaled based on the
    * current scaling factors.
    * \param x The x position in level space
    * \param y The y position in level space
    */
    void render(int x, int y, SDL_Rect* clip = nullptr, double scale_x  = 1.0, double scale_y = 1.0);

    int get_width();
    int get_height();
    std::string get_file_path();

private:
    SDL_Texture* m_texture;
    SDL_Renderer* m_renderer;  // non-owning reference

    int w, h;

    std::string file_path;
};

#endif
