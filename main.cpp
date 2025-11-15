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

#include "src/ecs/components/position.h"
#include "src/ecs/components/sprite.h"


void render_sprite(ECSManager& ecs, TextureManager* texture_manager, Entity& entity, Camera& camera, Window& window) {
    Sprite* sprite = ecs.get_component<Sprite>(entity);
    Texture* texture = texture_manager->get_texture(sprite->get_texture_name());
    SDL_Rect clip = sprite->get_sprite(0, 0);

    Position* position = ecs.get_component<Position>(entity);

    texture->render(
        position->get_x() - camera.get_x(),
        position->get_y() - camera.get_y(),
        &clip,
        window.get_scale_x(),
        window.get_scale_y()
    );
}


Entity* load_player(ECSManager& ecs) {
    std::unique_ptr<Entity> _player (new Entity(1));
    Entity* player = ecs.add_entity(std::move(_player));

    if (player == NULL) {
        return NULL;
    }

    std::unique_ptr<Sprite> player_sprite (new Sprite("resources/sprites/link.png", 16, 16));
    ecs.add_component<Sprite>(*player, std::move(player_sprite));

    std::unique_ptr<Position> player_position (new Position(0, 0));
    ecs.add_component<Position>(*player, std::move(player_position));

    return player;
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
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        // not indicative of how we'll be rendering stuff
        Texture* background = manager->get_texture("resources/screen_01.png");
        background->render(
            0, 0, NULL, window.get_scale_x(), window.get_scale_y()
        );

        render_sprite(ecs, manager.get(), player, camera, window);

        SDL_RenderPresent(renderer);
    }

    teardown_sdl();
}
