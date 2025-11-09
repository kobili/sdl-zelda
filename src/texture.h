#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"


class Texture {
public:
    Texture();
    ~Texture();

    void free();
    bool load_texture(SDL_Renderer* renderer, const char* path);

    void render(int x, int y, SDL_Rect* clip = nullptr, int scale_x = 0, int scale_y = 0);

    int get_width();
    int get_height();

private:
    SDL_Texture* m_texture;
    SDL_Renderer* m_renderer;

    int w, h;
};

#endif
