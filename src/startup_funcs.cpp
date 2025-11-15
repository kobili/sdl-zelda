#include "startup_funcs.h"
#include "ecs/components/sprite.h"
#include "ecs/components/position.h"
#include "ecs/components/velocity.h"
#include "ecs/components/movement.h"


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

    std::unique_ptr<Sprite> _player_sprite (new Sprite("resources/sprites/link.png", 16, 16));
    Sprite* player_sprite = ecs.add_component<Sprite>(*player, std::move(_player_sprite));
    if (player_sprite == NULL) {
        printf("failed to add Sprite component for Player\n");
        return NULL;
    }

    std::unique_ptr<Position> _player_position (new Position(0, 0));
    Position* position = ecs.add_component<Position>(*player, std::move(_player_position));
    if (position == NULL) {
        printf("failed to add Position for player\n");
        return NULL;
    }

    std::unique_ptr<Velocity> _player_velocity (new Velocity());
    Velocity* velocity = ecs.add_component<Velocity>(*player, std::move(_player_velocity));
    if (velocity == NULL) {
        printf("failed to add Velocity for player\n");
        return NULL;
    }

    std::unique_ptr<Movement> _movement (new Movement());
    Movement* movement = ecs.add_component<Movement>(*player, std::move(_movement));
    if (movement == NULL) {
        printf("failed to add Movement for player\n");
        return NULL;
    }

    return player;
}
