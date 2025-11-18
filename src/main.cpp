#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include "SDL.h"

#include "constants.h"
#include "sdl_utils.h"
#include "window.h"
#include "input_manager.h"
#include "startup_funcs.h"
#include "texture_manager.h"
#include "cameras/zone_camera.h"
#include "cameras/panning_camera.h"

#include "ecs/entity.h"

#include "ecs/managers/ecs_manager.h"


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

    InputManager input_manager;

    load_systems(ecs, input_manager, manager.get(), _camera.get(), &window);
    if (load_player(ecs) == NULL) {
        printf("failed to load player. Exiting...\n");
        return -1;
    }
    if (load_enemy(ecs) == NULL) {
        printf("failed to load enemy. Exiting...\n");
        return -1;
    }

    SDL_Event e;
    int running = 1;

    Uint32 start_time = SDL_GetTicks64();

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }

            window.handle_event(e);
            camera.handle_event(e);

            input_manager.handle_input(e);
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

        Uint32 current_time = SDL_GetTicks64();
        Uint32 dt = current_time - start_time;
        start_time = current_time;

        camera.move();
        ecs.update(dt);

        SDL_RenderPresent(renderer);

        input_manager.flush_mouse_events();
        input_manager.flush_keyboard_events();
    }

    teardown_sdl();
}
