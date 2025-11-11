#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"
#include <string>
#include "observer.h"


class Texture : public Observer {
public:
    Texture();
    ~Texture();

    void free();
    bool load_texture(SDL_Renderer* renderer, const char* path);

    void render(int x, int y, SDL_Rect* clip = nullptr);

    int get_width();
    int get_height();

    void observe(int w, int h) override;

private:
    SDL_Texture* m_texture;
    SDL_Renderer* m_renderer;

    int w, h;

    double scaling_factor_x, scaling_factor_y;

    std::string file_path;
};

#endif
