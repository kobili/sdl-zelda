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

#include "src/ecs/components/position.h"
#include "src/ecs/components/sprite.h"
#include "src/ecs/components/movement.h"
#include "src/ecs/components/velocity.h"
#include "src/ecs/components/player.h"


void move_entity(ECSManager& ecs, Entity* entity) {
    Movement* movement = ecs.get_component<Movement>(*entity);
    if (movement == NULL) {
        return;
    }

    Velocity* _velocity = ecs.get_component<Velocity>(*entity);
    if (_velocity == NULL) {
        return;
    }
    Velocity& velocity = *_velocity;

    Position* _position = ecs.get_component<Position>(*entity);
    if (_position == NULL) {
        return;
    }
    Position& position = *_position;

    position.set_x(position.get_x() + velocity.get_x());
    position.set_y(position.get_y() + velocity.get_y());
}


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

    ECSManager ecs;

    SpriteRenderSystem sprite_render_system = SpriteRenderSystem(&ecs, manager.get(), _camera.get(), &window);
    PlayerInputSystem player_input_system = PlayerInputSystem(&ecs);

    Entity* _player = load_player(ecs);
    if (_player == NULL) {
        printf("failed to load player. Exiting...\n");
        return -1;
    }
    Entity& player = *_player;

    SDL_Event e;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }

            window.handle_event(e);
            player_input_system.handle_input(e);
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        // not indicative of how we'll be rendering stuff
        Texture* background = manager->get_texture("resources/screen_01.png");
        background->render(
            0, 0, NULL, window.get_scale_x(), window.get_scale_y()
        );
        
        move_entity(ecs, &player);
        sprite_render_system.update();

        SDL_RenderPresent(renderer);
    }

    teardown_sdl();
}
