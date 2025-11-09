#include "texture.h"

#include "SDL_image.h"

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


bool Texture::load_texture(SDL_Renderer* renderer, const char* path) {
    free();

    m_renderer = renderer;

    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) {
        printf("Failed to load image surface: %s\n", IMG_GetError());
        return false;
    }

    w = surface->w;
    h = surface->h;

    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (m_texture == NULL) {
        printf("Failed to load texture: %s\n", SDL_GetError());
        return false;
    }

    file_path = path;

    return true;
}


void Texture::render(int x, int y, SDL_Rect* clip, int scale_x, int scale_y) {
    if (m_renderer == NULL) {
        printf("Texture has no renderer attached. Skipping render operation\n");
        return;
    }

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    if (clip != nullptr) {
        dst.w = clip->w;
        dst.h = clip->h;
    }

    if (scale_x) {
        dst.w = dst.w * scale_x;
    }

    if (scale_y) {
        dst.h = dst.h * scale_y;
    }

    SDL_RenderCopy(
        m_renderer,
        m_texture,
        clip != nullptr ? clip : NULL,
        &dst
    );
}


int Texture::get_width() {
    return w;
}


int Texture::get_height() {
    return h;
}
