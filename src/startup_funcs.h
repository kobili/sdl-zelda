#ifndef STARTUP_FUNCS_H
#define STARTUP_FUNCS_H

#include <vector>

#include "texture_manager.h"
#include "cameras/camera.h"
#include "window.h"
#include "ecs/managers/ecs_manager.h"

bool load_textures(TextureManager* manager);
Entity* load_player(ECSManager& ecs);
Entity* load_enemy(ECSManager& ecs);
void load_systems(ECSManager& ecs, TextureManager* texture_manager, Camera* camera, Window* window);

#endif
