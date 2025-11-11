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
#include "src/resource_manager.h"
#include "src/tiles/tileset.h"
#include "src/tiles/tile.h"
#include "src/startup_funcs.h"
#include "src/camera.h"


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

    ResourceManager manager(&window);

    if (!load_resources(&manager)) {
        return -1;
    }

    Texture* full_overworld = manager.get_texture("resources/overworld__full.png");
    
    Camera camera(7 * NES_SCREEN_WIDTH, 7 * NES_SCREEN_HEIGHT);
    Player player = Player(manager.get_sprite("resources/sprites/link.png"));
    player.set_x(7 * NES_SCREEN_WIDTH);
    player.set_y(7 * NES_SCREEN_HEIGHT);

    Enemy enemy = Enemy(manager.get_sprite("resources/sprites/oktorok__red.png"));
    enemy.set_x(7 * NES_SCREEN_WIDTH + NES_SCREEN_WIDTH / 2);
    enemy.set_y(7 * NES_SCREEN_HEIGHT + NES_SCREEN_HEIGHT / 2);

    std::vector<SDL_Rect*> colliders;
    colliders.push_back(&enemy.get_collider());

    SDL_Event e;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }

            window.handle_event(e);
            camera.handle_event(e);
            player.handle_event(e);
        }

        camera.move();
        player.move(colliders);

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        full_overworld->render(0 - camera.get_x(), 0 - camera.get_y(), NULL);
        player.render(camera);
        enemy.render(camera);

        SDL_RenderPresent(renderer);
    }

    teardown_sdl();
}
