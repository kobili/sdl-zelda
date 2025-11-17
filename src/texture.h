#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"
#include <string>


struct RGB {
    Uint8 r;
    Uint8 g;
    Uint8 b;
};


class Texture {
public:
    Texture();
    ~Texture();

    void free();
    bool load_texture(SDL_Renderer* renderer, const char* path, RGB* colour_key = nullptr);

    /**
    * Render the texture at x, y in the world. The position will be scaled based on the
    * current scaling factors.
    * \param x The x position in screen space
    * \param y The y position in screen space
    * \param clip The portion of the texture to render
    * \param scale_x The horizontal scaling factor by which to stretch the rendered texture
    * \param scale_y The vertical scaling factor by which to stretch the rendered texture
    * \param flip_horizontal Whether or not the texture should be flipped on the horizontal axis
    * \param flip_vertical Whether or not the texture should be flipped on the vertical axis
    */
    void render(
        int x,
        int y,
        SDL_Rect* clip = nullptr,
        double scale_x = 1.0,
        double scale_y = 1.0,
        bool flip_horizontal = false,
        bool flip_vertical = false
    );

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
