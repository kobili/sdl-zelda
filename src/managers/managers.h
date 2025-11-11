#ifndef MANAGERS_H
#define MANAGERS_H

#include <memory>
#include <vector>

#include "texture_manager.h"
#include "sprite_manager.h"

#include "../window.h"

std::unique_ptr<TextureManager> load_textures(Window* window);
std::unique_ptr<SpriteManager> load_sprites(TextureManager* textures);

#endif
