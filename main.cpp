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
#include "src/texture_manager.h"
#include "src/sprite_manager.h"
#include "src/tileset.h"


std::unique_ptr<TextureManager> load_textures(Window* window) {
    std::vector<std::string> texture_files = {
        "resources/screen_01.png",
        "resources/link_walk_sprite.png",
        "resources/oktorok_sprites.png",
        "resources/tileset_overworld_forest.png",
        "resources/tileset_overworld_death_mountain.png"
    };

    std::unique_ptr<TextureManager> texture_manager (new TextureManager(window));
    for (int i = 0; i < texture_files.size(); i++) {
        std::string file_path = texture_files[i];
        if (!texture_manager->load_texture(file_path)) {
            printf("failed to load texture: %s. Exiting...\n", file_path.c_str());
            return NULL;
        }
    }

    return texture_manager;
}


std::unique_ptr<SpriteManager> load_sprites(TextureManager* textures) {
    std::vector<std::string> texture_files = {
        "resources/link_walk_sprite.png",
        "resources/oktorok_sprites.png",
    };

    std::unique_ptr<SpriteManager> sprite_manager (new SpriteManager());
    for (int i = 0; i < texture_files.size(); i++) {
        std::string texture_file = texture_files[i];

        Texture* texture = textures->get_texture(texture_file);
        if (!sprite_manager->load_sprite(texture, 16, 16)) {
            printf("failed to load sprite for %s\n", texture_file.c_str());
            return NULL;
        }
    }

    return sprite_manager;
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

        render_screen_01(tileset);
        
        // player.render();
        // oktorok.render();

        SDL_RenderPresent(renderer);
    }

    teardown_sdl();
}
