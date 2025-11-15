#ifndef STARTUP_FUNCS_H
#define STARTUP_FUNCS_H

#include <vector>

#include "texture_manager.h"
#include "ecs/ecs_manager.h"

bool load_textures(TextureManager* manager);
Entity* load_player(ECSManager& ecs);
Entity* load_enemy(ECSManager& ecs);

#endif
