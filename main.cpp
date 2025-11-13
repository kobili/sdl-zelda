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
#include "src/cameras/panning_camera.h"
#include "src/cameras/zone_camera.h"


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
    
    Player player = Player(manager.get_sprite("resources/sprites/link.png"));
    player.set_x(7 * NES_SCREEN_WIDTH);
    player.set_y(7 * NES_SCREEN_HEIGHT);
    Zone player_zone = player.get_current_zone();

    std::unique_ptr<Camera> _camera(new ZoneCamera(player_zone.row * NES_SCREEN_WIDTH, player_zone.col * NES_SCREEN_HEIGHT, &window));
    Camera& camera = *_camera;


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

        // Zone current_zone = camera.get_current_zone();
        // printf("currently in zone %d-%d\n", current_zone.col, current_zone.row);

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        full_overworld->render(
            0 - camera.get_x(),
            0 - camera.get_y(),
            NULL,
            camera.get_scale_x(),
            camera.get_scale_y()
        );
        player.render(camera);
        enemy.render(camera);

        SDL_RenderPresent(renderer);
    }

    teardown_sdl();
}
