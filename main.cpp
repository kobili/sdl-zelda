#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <memory>

#include "SDL.h"
#include "SDL_image.h"

#include "src/constants.h"
#include "src/sdl_utils.h"
#include "src/window.h"
#include "src/startup_funcs.h"
#include "src/texture_manager.h"
#include "src/cameras/zone_camera.h"

#include "src/ecs/ecs_manager.h"

#include "src/ecs/systems/sprite_renderer.h"
#include "src/ecs/systems/player_input.h"
#include "src/ecs/systems/movement_system.h"
#include "src/ecs/systems/click_system.h"

#include "src/ecs/components/position.h"
#include "src/ecs/components/sprite.h"
#include "src/ecs/components/movement.h"
#include "src/ecs/components/velocity.h"
#include "src/ecs/components/player.h"


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

    std::unique_ptr<Camera> _camera (new ZoneCamera(7 * NES_SCREEN_WIDTH, 7 * NES_SCREEN_HEIGHT));
    Camera& camera = *_camera;

    std::unique_ptr<TextureManager> manager(new TextureManager(&window));
    if (!load_textures(manager.get())) {
        return -1;
    }

    ECSManager ecs;

    SpriteRenderSystem sprite_render_system = SpriteRenderSystem(&ecs, manager.get(), _camera.get(), &window);
    PlayerInputSystem player_input_system = PlayerInputSystem(&ecs);
    ClickSystem click_system = ClickSystem(&ecs, &window, _camera.get());
    MovementSystem movement_system = MovementSystem(&ecs);

    Entity* _player = load_player(ecs);
    if (_player == NULL) {
        printf("failed to load player. Exiting...\n");
        return -1;
    }
    Entity& player = *_player;

    Entity* _enemy = load_enemy(ecs);
    if (_enemy == NULL) {
        printf("failed to load enemy. Exiting...\n");
        return -1;
    }
    Entity& enemy = *_enemy;

    SDL_Event e;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }

            window.handle_event(e);
            camera.handle_event(e);
            click_system.handle_input(e);
            player_input_system.handle_input(e);
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        // not indicative of how we'll be rendering stuff
        Texture* background = manager->get_texture("resources/overworld__full.png");
        background->render(
            0 - camera.get_x(),
            0 - camera.get_y(),
            NULL,
            window.get_scale_x(),
            window.get_scale_y()
        );

        camera.move();

        movement_system.update();
        sprite_render_system.update();

        SDL_RenderPresent(renderer);
    }

    teardown_sdl();
}
