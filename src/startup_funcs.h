#ifndef STARTUP_FUNCS_H
#define STARTUP_FUNCS_H

#include <vector>

#include "texture_manager.h"
#include "cameras/camera.h"
#include "window.h"
#include "input_manager.h"
#include "ecs/managers/ecs_manager.h"

bool load_textures(TextureManager* manager);
void load_player(ECSManager& ecs);
void load_enemy(ECSManager& ecs);
void load_sword_attack_animation(ECSManager& ecs, int player_entity);
void load_systems(ECSManager& ecs, InputManager& input_manager, TextureManager* texture_manager, Camera* camera, Window* window);

#endif
