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

#include "src/ecs/entity.h"
#include "src/ecs/components/sprite.h"
#include "src/ecs/components/position.h"


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

    std::unique_ptr<Camera> _camera (new ZoneCamera(0, 0));
    Camera& camera = *_camera;

    std::unique_ptr<TextureManager> manager(new TextureManager(&window));
    if (!load_textures(manager.get())) {
        return -1;
    }

    Entity player = Entity(1);
    Sprite player_sprite = Sprite("resources/sprites/link.png", 16, 16);
    Position player_position = Position(0, 0);

    SDL_Event e;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }

            window.handle_event(e);
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        // not indicative of how we'll be rendering stuff
        Texture* background = manager->get_texture("resources/screen_01.png");
        background->render(
            0, 0, NULL, window.get_scale_x(), window.get_scale_y()
        );

        Texture* texture = manager->get_texture(player_sprite.get_texture_name());
        SDL_Rect clip = player_sprite.get_sprite(0, 0); // this should come from an animator or something
        texture->render(
            player_position.get_x() - camera.get_x(),
            player_position.get_y() - camera.get_y(),
            &clip,
            window.get_scale_x(),
            window.get_scale_y()
        );

        SDL_RenderPresent(renderer);
    }

    teardown_sdl();
}
