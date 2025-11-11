#ifndef STARTUP_FUNCS_H
#define STARTUP_FUNCS_H

#include <vector>

#include "resource_manager.h"
#include "tiles/tile.h"
#include "tiles/tileset.h"

bool load_resources(ResourceManager* manager);
std::vector<Tile> get_screen_1_tiles(Tileset* tileset);

#endif
