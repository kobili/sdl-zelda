#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

#include "src/constants.h"
#include "src/window.h"
#include "src/texture.h"
#include "src/sprite_sheet.h"
#include "src/sdl_utils.h"
#include "src/player.h"
#include "src/enemy.h"
#include "src/texture_manager.h"


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

    TextureManager texture_manager(&window);

    std::vector<std::string> texture_files = {
        "resources/screen_01.png",
        "resources/link_walk_sprite.png",
        "resources/oktorok_sprites.png",
    };

    for (int i = 0; i < texture_files.size(); i++) {
        std::string file_path = texture_files[i];
        if (!texture_manager.load_texture(file_path)) {
            printf("failed to load texture: %s. Exiting...\n", file_path.c_str());
            return -1;
        }
    }

    Texture* background = texture_manager.get_texture("resources/screen_01.png");

    Player player;
    SpriteSheet sprite_sheet;
    sprite_sheet.load_sprite_sheet(texture_manager.get_texture("resources/link_walk_sprite.png"), 16, 16);
    player.set_sprite_sheet(&sprite_sheet);

    Enemy oktorok;
    SpriteSheet oktorok_sprite_sheet;
    oktorok_sprite_sheet.load_sprite_sheet(texture_manager.get_texture("resources/oktorok_sprites.png"), 16, 16);
    oktorok.set_sprite_sheet(&oktorok_sprite_sheet);
    oktorok.set_x(NES_SCREEN_WIDTH / 2 - 8);
    oktorok.set_y(NES_SCREEN_HEIGHT / 2 - 8);

    std::vector<SDL_Rect*> colliders;
    colliders.push_back(&oktorok.get_collider());

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

        background->render(0, 0, NULL);

        player.render();

        oktorok.render();

        SDL_RenderPresent(renderer);
    }

    teardown_sdl();
}
