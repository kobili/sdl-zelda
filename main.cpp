#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "src/constants.h"
#include "src/window.h"
#include "src/texture.h"
#include "src/sprite_sheet.h"
#include "src/sdl_utils.h"
#include "src/player.h"
#include "src/enemy.h"


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

    Texture background;
    if (!background.load_texture(renderer, "resources/screen_01.png")) {
        printf("failed to load background. Exiting...\n");
        return -1;
    }

    Player player;
    SpriteSheet* sprite_sheet = new SpriteSheet();
    if (!sprite_sheet->load_sprite_sheet(renderer, "resources/link_walk_sprite.png", 16, 16)) {
        printf("failed to create sprite sheet. Exiting...\n");
        return -1;
    }
    player.set_sprite_sheet(sprite_sheet);

    Enemy oktorok;
    SpriteSheet* oktorok_sprite_sheet = new SpriteSheet();
    if (!oktorok_sprite_sheet->load_sprite_sheet(renderer, "resources/oktorok_sprites.png", 16, 16)) {
        printf("failed to load oktorok sprites. Exiting...\n");
        return -1;
    }
    oktorok.set_sprite_sheet(oktorok_sprite_sheet);
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

            player.handle_event(e);
        }

        player.move(colliders);

        int scaling_factor_x = window.get_width() / NES_SCREEN_WIDTH;
        int scaling_factor_y = window.get_height() / NES_SCREEN_HEIGHT;

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        background.render(0, 0, NULL, scaling_factor_x, scaling_factor_y);

        player.render(scaling_factor_x, scaling_factor_y);

        oktorok.render(scaling_factor_x, scaling_factor_y);

        SDL_RenderPresent(renderer);
    }

    teardown_sdl();
}
