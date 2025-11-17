#include "texture.h"

#include "SDL_image.h"
#include <cmath>

#include "constants.h"

Texture::Texture() {
    m_texture = NULL;
    m_renderer = NULL;
    w = 0;
    h = 0;

    file_path = "";
}


Texture::~Texture() {
    free();
    printf("Destroyed texture %s\n", file_path.c_str());
}


void Texture::free() {
    if (m_texture != NULL) {
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;
    }

    if (m_renderer != NULL) {
        m_renderer = NULL;
    }

    w = 0;
    h = 0;
}


bool Texture::load_texture(SDL_Renderer* renderer, const char* path, RGB* colour_key) {
    free();

    m_renderer = renderer;

    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) {
        printf("Failed to load image surface: %s\n", IMG_GetError());
        return false;
    }

    w = surface->w;
    h = surface->h;

    if (colour_key != nullptr) {
        SDL_SetColorKey(
            surface,
            SDL_TRUE,
            SDL_MapRGB(surface->format, colour_key->r, colour_key->g, colour_key->b)
        );
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (m_texture == NULL) {
        printf("Failed to load texture: %s\n", SDL_GetError());
        return false;
    }

    file_path = path;

    return true;
}


void Texture::render(
    int x,
    int y,
    SDL_Rect* clip,
    double scale_x,
    double scale_y,
    bool flip_horizontal,
    bool flip_vertical
) {
    if (m_renderer == NULL) {
        printf("Texture has no renderer attached. Skipping render operation\n");
        return;
    }

    SDL_Rect dst = {x, y, w, h};

    if (clip != nullptr) {
        dst.w = clip->w;
        dst.h = clip->h;
    }

    if (scale_x) {
        dst.x = std::round(dst.x * scale_x);
        dst.w = std::round(dst.w * scale_x);
    }

    if (scale_y) {
        dst.y = std::round(dst.y * scale_y);
        dst.h = std::round(dst.h * scale_y);
    }

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (flip_horizontal) {
        flip = SDL_FLIP_HORIZONTAL;
    }
    if (flip_vertical) {
        flip = SDL_FLIP_VERTICAL;
    }

    SDL_RenderCopyEx(
        m_renderer,
        m_texture,
        clip,
        &dst,
        0.0,
        NULL,
        flip
    );
}


int Texture::get_width() {
    return w;
}


int Texture::get_height() {
    return h;
}


std::string Texture::get_file_path() {
    return file_path;
}
