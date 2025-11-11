#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"

#include "src/constants.h"
#include "src/window.h"
#include "src/texture.h"
#include "src/sprite_sheet.h"
#include "src/sdl_utils.h"
#include "src/player.h"
#include "src/enemy.h"
#include "src/managers/texture_manager.h"
#include "src/managers/sprite_manager.h"
#include "src/managers/managers.h"
#include "src/tiles/tileset.h"
#include "src/tiles/tile.h"


int main(int argc, char* args[]) {
    if (init_sdl() < 0) {
        return -1;
    }

    Window window;
    if (!window.init()) {
        printf("Failed to create window. Exiting...\n");
        return -1;
    }
    SDL_Renderer* renderer = window.get_renderer();

    auto texture_manager = load_textures(&window);
    auto sprite_manager = load_sprites(texture_manager.get());

    Texture* background = texture_manager->get_texture("resources/screen_01.png");

    Player player = Player(sprite_manager->get_sprite("resources/link_walk_sprite.png"));

    Enemy oktorok = Enemy(sprite_manager->get_sprite("resources/oktorok_sprites.png"));
    oktorok.set_x(NES_SCREEN_WIDTH / 2 - 8);
    oktorok.set_y(NES_SCREEN_HEIGHT / 2 - 8);

    std::vector<SDL_Rect*> colliders;
    colliders.push_back(&oktorok.get_collider());

    Tileset tileset = Tileset(texture_manager->get_texture("resources/tileset_overworld_forest.png"), 16, 16);

    std::vector<Tile> tiles = get_screen_1_tiles(&tileset);

    SDL_Event e;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }

            window.handle_event(e);
            player.handle_event(e);
        }

        player.move(colliders);

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        // background->render(0, 0, NULL);

        for (int i = 0; i < tiles.size(); i++) {
            tiles[i].render();
        }
        
        // player.render();
        // oktorok.render();

        SDL_RenderPresent(renderer);
    }

    teardown_sdl();
}
