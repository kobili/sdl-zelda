#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_image.h"

#include "src/constants.h"
#include "src/window.h"
#include "src/texture.h"
#include "src/sprite_sheet.h"
#include "src/sdl_utils.h"


int main(int argc, char* args[]) {
    if (init_sdl() < 0) {
        return -1;
    }

    Window* window = create_window();
    if (window == NULL) {
        printf("Failed to create window. Exiting...\n");
        return -1;
    }
    SDL_Renderer* renderer = window->renderer;

    SpriteSheet* sprite_sheet = create_sprite_sheet(renderer, "resources/link_walk_sprite.png", 16, 16);
    if (sprite_sheet == NULL) {
        printf("failed to create sprite sheet. Exiting...\n");
        return -1;
    }

    SDL_Event e;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);

        SDL_Rect src = get_sprite(sprite_sheet, 0, 0);

        SDL_RenderCopy(
            renderer,
            sprite_sheet->texture->texture,
            &src,
            NULL
        );

        SDL_RenderPresent(renderer);
    }

    free_sprite_sheet(sprite_sheet);

    free_window(window);
    window = NULL;

    teardown_sdl();
}
