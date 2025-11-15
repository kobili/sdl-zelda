#include "startup_funcs.h"
#include "constants.h"
#include "ecs/components/sprite.h"
#include "ecs/components/position.h"
#include "ecs/components/velocity.h"
#include "ecs/components/movement.h"
#include "ecs/components/player.h"
#include "ecs/components/collider.h"


bool load_textures(TextureManager* manager) {
    std::vector<std::string> texture_files = {
        "resources/screen_01.png",
        "resources/sprites/link.png",
        "resources/overworld__full.png",
        "resources/sprites/oktorok__red.png",
        "resources/tilesets/overworld__forest.png",
        "resources/tilesets/overworld__death_mountain.png"
    };

    for (int i = 0; i < texture_files.size(); i++) {
        std::string file_path = texture_files[i];
        if (!manager->load_texture(file_path)) {
            printf("failed to load texture: %s. Exiting...\n", file_path.c_str());
            return false;
        }
    }

    return true;
}


Entity* load_player(ECSManager& ecs) {
    std::unique_ptr<Entity> _player (new Entity(1));
    Entity* player = ecs.add_entity(std::move(_player));

    if (player == NULL) {
        return NULL;
    }

    std::unique_ptr<Sprite> sprite (new Sprite("resources/sprites/link.png", 16, 16));
    if (ecs.add_component<Sprite>(*player, std::move(sprite)) == NULL) {
        printf("failed to add Sprite component for Player\n");
        return NULL;
    }

    std::unique_ptr<Position> position (new Position(
        7 * NES_SCREEN_WIDTH, 7 * NES_SCREEN_HEIGHT
    ));
    if (ecs.add_component<Position>(*player, std::move(position)) == NULL) {
        printf("failed to add Position for player\n");
        return NULL;
    }

    std::unique_ptr<Velocity> velocity (new Velocity());
    if (ecs.add_component<Velocity>(*player, std::move(velocity)) == NULL) {
        printf("failed to add Velocity for player\n");
        return NULL;
    }

    std::unique_ptr<Movement> movement (new Movement());
    if (ecs.add_component<Movement>(*player, std::move(movement)) == NULL) {
        printf("failed to add Movement for player\n");
        return NULL;
    }

    std::unique_ptr<Player> player_comp (new Player());
    if (ecs.add_component<Player>(*player, std::move(player_comp)) == NULL) {
        printf("failed to load player component for player\n");
        return NULL;
    }

    std::unique_ptr<Collider> collider (new Collider(
        7 * NES_SCREEN_WIDTH, 7 * NES_SCREEN_HEIGHT, 16, 16
    ));
    if (ecs.add_component<Collider>(*player, std::move(collider)) == NULL) {
        printf("failed to load collider for player\n");
        return NULL;
    }

    return player;
}


Entity* load_enemy(ECSManager& ecs) {
    std::unique_ptr<Entity> _enemy (new Entity(2));
    Entity* enemy = ecs.add_entity(std::move(_enemy));

    if (enemy == NULL) {
        return NULL;
    }

    std::unique_ptr<Sprite> sprite (new Sprite("resources/sprites/oktorok__red.png", 16, 16));
    if (ecs.add_component<Sprite>(*enemy, std::move(sprite)) == NULL) {
        printf("failed to add Sprite component for Player\n");
        return NULL;
    }

    std::unique_ptr<Position> position (new Position(
        7 * NES_SCREEN_WIDTH + NES_SCREEN_WIDTH / 2,
        7 * NES_SCREEN_HEIGHT + NES_SCREEN_HEIGHT / 2
    ));
    if (ecs.add_component<Position>(*enemy, std::move(position)) == NULL) {
        printf("failed to add Position for player\n");
        return NULL;
    }

    std::unique_ptr<Velocity> velocity (new Velocity());
    if (ecs.add_component<Velocity>(*enemy, std::move(velocity)) == NULL) {
        printf("failed to add Velocity for player\n");
        return NULL;
    }

    std::unique_ptr<Collider> collider (new Collider(
        7 * NES_SCREEN_WIDTH + NES_SCREEN_WIDTH / 2,
        7 * NES_SCREEN_HEIGHT + NES_SCREEN_HEIGHT / 2,
        16,
        16
    ));
    if (ecs.add_component<Collider>(*enemy, std::move(collider)) == NULL) {
        printf("failed to load collider for player\n");
        return NULL;
    }

    return enemy;
}
