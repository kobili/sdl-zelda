#include "startup_funcs.h"

#include "constants.h"

#include "ecs/components/sprite.h"
#include "ecs/components/position.h"
#include "ecs/components/velocity.h"
#include "ecs/components/movement.h"
#include "ecs/components/player.h"
#include "ecs/components/collider.h"
#include "ecs/components/clickable.h"
#include "ecs/components/sprite_animation.h"
#include "ecs/components/character.h"

#include "ecs/systems/click_system.h"
#include "ecs/systems/movement_system.h"
#include "ecs/systems/player_movement_input.h"
#include "ecs/systems/sprite_renderer.h"
#include "ecs/systems/sprite_animation_system.h"
#include "ecs/systems/player_attack_input.h"
#include "ecs/systems/character_update.h"


bool load_textures(TextureManager* manager) {
    std::vector<std::string> texture_files = {
        "resources/screen_01.png",
        "resources/overworld__full.png",
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

    std::vector<std::string> sprite_files = {
        "resources/sprites/link.png",
        "resources/sprites/oktorok__red.png",
        "resources/sprites/wood_sword_sprites.png"
    };
    RGB grey_colour_key = {116, 116, 116};

    for (int i = 0; i < sprite_files.size(); i++) {
        std::string file_path = sprite_files[i];
        if (!manager->load_texture(file_path, &grey_colour_key)) {
            printf("failed to load texture: %s. Exiting...\n", file_path.c_str());
            return false;
        }
    }

    return true;
}


std::unique_ptr<SpriteAnimation> load_player_animations() {
    std::unique_ptr<SpriteAnimation> animation (new SpriteAnimation());

    // setup idle animation
    std::vector<AnimationFrameData> idle_up_frames = {
        {4, 0, false, false}  
    };

    std::vector<AnimationFrameData> idle_down_frames = {
        {0, 0, false, false}
    };

    std::vector<AnimationFrameData> idle_left_frames = {
        {2, 0, true, false}
    };

    std::vector<AnimationFrameData> idle_right_frames = {
        {2, 0, false, false}
    };

    AnimationSet idle_animation_set = {
        100,
        {idle_up_frames, idle_down_frames, idle_left_frames, idle_right_frames}
    };

    animation->set_animation_set(CharacterState::IDLE, idle_animation_set);

    // setup movement animation
    std::vector<AnimationFrameData> move_up_frames = {
        {4, 0, false, false},
        {5, 0, false, false}
    };

    std::vector<AnimationFrameData> move_down_frames = {
        {0, 0, false, false},
        {1, 0, false, false}
    };

    std::vector<AnimationFrameData> move_right_frames = {
        {2, 0, false, false},
        {3, 0, false, false}
    };

    std::vector<AnimationFrameData> move_left_frames = {
        {2, 0, true, false},
        {3, 0, true, false}
    };

    AnimationSet movement_animation_set = {
        100,
        {move_up_frames, move_down_frames, move_left_frames, move_right_frames}
    };

    animation->set_animation_set(CharacterState::MOVING, movement_animation_set);


    // setup attack animations
    std::vector<AnimationFrameData> attack_up_frames = {
        {8, 1, false, false},
        {9, 1, false, false},
        {10, 1, false, false},
        {11, 1, false, false}
    };
    std::vector<AnimationFrameData> attack_down_frames = {
        {0, 1, false, false},
        {1, 1, false, false},
        {2, 1, false, false},
        {3, 1, false, false}
    };
    std::vector<AnimationFrameData> attack_left_frames = {
        {4, 1, true, false},
        {5, 1, true, false},
        {6, 1, true, false},
        {7, 1, true, false}
    };
    std::vector<AnimationFrameData> attack_right_frames = {
        {4, 1, false, false},
        {5, 1, false, false},
        {6, 1, false, false},
        {7, 1, false, false},
    };
    AnimationSet attack_animation_set = {
        LINK_ATTACK_ANIMATION_FRAME_DURATION_MS,
        {attack_up_frames, attack_down_frames, attack_left_frames, attack_right_frames}
    };

    animation->set_animation_set(CharacterState::ATTACKING, attack_animation_set);

    return animation;
}


Entity* load_player(ECSManager& ecs) {
    std::unique_ptr<Entity> _player (new Entity(1));
    Entity* player = ecs.add_entity(std::move(_player));

    if (player == NULL) {
        return NULL;
    }

    std::unique_ptr<Character> character (new Character(Direction::DOWN, CharacterState::IDLE, LINK_ATTACK_DURATION_MS));
    ecs.add_component(*player, std::move(character));

    std::unique_ptr<Sprite> sprite (new Sprite("resources/sprites/link.png", 16, 16));
    if (ecs.add_component<Sprite>(*player, std::move(sprite)) == NULL) {
        printf("failed to add Sprite component for Player\n");
        return NULL;
    }

    std::unique_ptr<Position> position (new Position(
        (7 * NES_SCREEN_WIDTH + NES_SCREEN_WIDTH / 2) - 16,
        7 * NES_SCREEN_HEIGHT + NES_SCREEN_HEIGHT / 2
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
        (7 * NES_SCREEN_WIDTH + NES_SCREEN_WIDTH / 2) - 16,
        7 * NES_SCREEN_HEIGHT + NES_SCREEN_HEIGHT / 2
        ,
        16,
        16
    ));
    if (ecs.add_component<Collider>(*player, std::move(collider)) == NULL) {
        printf("failed to load collider for player\n");
        return NULL;
    }

    ClickHandler on_click = [&ecs](Entity& entity) {
        Position& player_position = *ecs.get_component<Position>(entity);
        printf("Player at (%d, %d)\n", player_position.get_x(), player_position.get_y());
    };

    std::unique_ptr<Clickable> clickable (new Clickable(on_click));
    if (ecs.add_component<Clickable>(*player, std::move(clickable)) == NULL) {
        printf("failed to load clickable for player\n");
    }

    auto animation = load_player_animations();
    if (ecs.add_component<SpriteAnimation>(*player, std::move(animation)) == NULL) {
        printf("failed to load player animations");
    }

    return player;
}


std::unique_ptr<SpriteAnimation> load_enemy_animation() {
    std::unique_ptr<SpriteAnimation> animation (new SpriteAnimation());

    std::vector<AnimationFrameData> idle_up_frames = {
        {0, 0, false, true},
        {1, 0, false, true}
    };

    std::vector<AnimationFrameData> idle_down_frames = {
        {0, 0, false, false},
        {1, 0, false, false}
    };

    std::vector<AnimationFrameData> idle_right_frames = {
        {2, 0, true, false},
        {3, 0, true, false}
    };

    std::vector<AnimationFrameData> idle_left_frames = {
        {2, 0, false, false},
        {3, 0, false, false}
    };
    std::vector<AnimationFrameData> idle_frames[4] = {
        idle_up_frames, idle_down_frames, idle_left_frames, idle_right_frames
    };

    AnimationSet idle_set = {
        200,
        {
            idle_up_frames, idle_down_frames, idle_left_frames, idle_right_frames
        }
    };

    animation->set_animation_set(CharacterState::IDLE, idle_set);

    return animation;
}


Entity* load_enemy(ECSManager& ecs) {
    std::unique_ptr<Entity> _enemy (new Entity(2));
    Entity* enemy = ecs.add_entity(std::move(_enemy));

    if (enemy == NULL) {
        return NULL;
    }

    std::unique_ptr<Character> character (new Character(Direction::LEFT, CharacterState::IDLE));
    ecs.add_component(*enemy, std::move(character));

    std::unique_ptr<Sprite> sprite (new Sprite("resources/sprites/oktorok__red.png", 16, 16));
    if (ecs.add_component<Sprite>(*enemy, std::move(sprite)) == NULL) {
        printf("failed to add Sprite component for enemy\n");
        return NULL;
    }

    std::unique_ptr<Position> position (new Position(
        7 * NES_SCREEN_WIDTH + NES_SCREEN_WIDTH / 2,
        7 * NES_SCREEN_HEIGHT + NES_SCREEN_HEIGHT / 2
    ));
    if (ecs.add_component<Position>(*enemy, std::move(position)) == NULL) {
        printf("failed to add Position for enemy\n");
        return NULL;
    }

    std::unique_ptr<Velocity> velocity (new Velocity());
    if (ecs.add_component<Velocity>(*enemy, std::move(velocity)) == NULL) {
        printf("failed to add Velocity for enemy\n");
        return NULL;
    }

    std::unique_ptr<Collider> collider (new Collider(
        7 * NES_SCREEN_WIDTH + NES_SCREEN_WIDTH / 2,
        7 * NES_SCREEN_HEIGHT + NES_SCREEN_HEIGHT / 2,
        16,
        16
    ));
    if (ecs.add_component<Collider>(*enemy, std::move(collider)) == NULL) {
        printf("failed to load collider for enemy\n");
        return NULL;
    }

    ClickHandler on_click = [&ecs](Entity& entity) {
        Sprite* _sprite_value = ecs.get_component<Sprite>(entity);
        if (_sprite_value == NULL) {
            return;
        }
        if (_sprite_value->get_texture_name() != "resources/sprites/oktorok__red.png") {
            return;
        }
        printf("I'm so hungry, I could eat an oktorok!\n");
        // entity.deactivate();
    };
    std::unique_ptr<Clickable> clickable (new Clickable(on_click));
    if (ecs.add_component<Clickable>(*enemy, std::move(clickable)) == NULL) {
        printf("failed to load clickable for enemy\n");
        return NULL;
    }
    
    std::unique_ptr<SpriteAnimation> animation = load_enemy_animation();
    if (ecs.add_component<SpriteAnimation>(*enemy, std::move(animation)) == NULL) {
        printf("failed to load animation for enemy.\n");
        return NULL;
    }

    return enemy;
}


Entity* load_sword_sprite(ECSManager& ecs) {

    int player_x = (7 * NES_SCREEN_WIDTH + NES_SCREEN_WIDTH / 2) - 16;
    int player_y = 7 * NES_SCREEN_HEIGHT + NES_SCREEN_HEIGHT / 2;

    std::unique_ptr<Entity> _entity (new Entity(3));
    Entity* entity = ecs.add_entity(std::move(_entity));

    std::unique_ptr<Sprite> sprite (new Sprite("resources/sprites/wood_sword_sprites.png", 16, 16));
    ecs.add_component<Sprite>(*entity, std::move(sprite));

    std::unique_ptr<Position> position (new Position(
        player_x + 5,
        player_y + 11
    ));
    ecs.add_component<Position>(*entity, std::move(position));

    // load animations
    std::unique_ptr<SpriteAnimation> animation (new SpriteAnimation());

    std::vector<AnimationFrameData> idle_up_frames = {
        {0, 0, false, false}
    };
    std::vector<AnimationFrameData>  idle_down_frames = {
        {-1, -1, false, true, 0, 0},
        // {0, 0, false, true, 0, 0},
        // {0, 0, false, true, 0, -4},
        // {0, 0, false, true, 0, -8},
    };
    std::vector<AnimationFrameData> idle_left_frames = {
        {1, 0, true, false}
    };
    std::vector<AnimationFrameData> idle_right_frames = {
        {1, 0, false, false}
    };
    animation->set_animation_set(CharacterState::IDLE, {
        LINK_ATTACK_ANIMATION_FRAME_DURATION_MS,
        {
            idle_up_frames, idle_down_frames, idle_left_frames, idle_right_frames
        }
    });

    std::vector<AnimationFrameData> attack_up_frames = {
        {0, 0, false, false}
    };
    std::vector<AnimationFrameData>  attack_down_frames = {
        {-1, -1, false, true, 0, 0},
        {0, 0, false, true, 0, 0},
        {0, 0, false, true, 0, -4},
        {0, 0, false, true, 0, -8},
    };
    std::vector<AnimationFrameData> attack_left_frames = {
        {1, 0, true, false}
    };
    std::vector<AnimationFrameData> attack_right_frames = {
        {1, 0, false, false}
    };
    animation->set_animation_set(CharacterState::ATTACKING, {
        LINK_ATTACK_ANIMATION_FRAME_DURATION_MS,
        {
            attack_up_frames, attack_down_frames, attack_left_frames, attack_right_frames
        }
    });

    ecs.add_component<SpriteAnimation>(*entity, std::move(animation));

    // TODO: Need a separate kind of animation for non character entities
    std::unique_ptr<Character> character (new Character(Direction::DOWN, CharacterState::IDLE, LINK_ATTACK_DURATION_MS));
    ecs.add_component<Character>(*entity, std::move(character));

    std::unique_ptr<Player> player (new Player());
    ecs.add_component<Player>(*entity, std::move(player));

    std::unique_ptr<Collider> collider (new Collider(
        player_x,
        player_y,
        16,
        16
    ));
    ecs.add_component<Collider>(*entity, std::move(collider));

    ClickHandler on_click = [&ecs](Entity& entity) {
        Sprite* _sprite_value = ecs.get_component<Sprite>(entity);
        if (_sprite_value == NULL) {
            return;
        }
        if (_sprite_value->get_texture_name() != "resources/sprites/wood_sword_sprites.png") {
            return;
        }
        Character* _character_value = ecs.get_component<Character>(entity);
        if (_character_value == NULL) {
            return;
        }

        // printf("Sword\n");
        // _character_value->set_character_state(CharacterState::ATTACKING);
        entity.deactivate();
    };
    std::unique_ptr<Clickable> clickable (new Clickable(on_click));
    if (ecs.add_component<Clickable>(*entity, std::move(clickable)) == NULL) {
        printf("failed to load clickable for enemy\n");
        return NULL;
    }

    return entity;
}


void load_systems(ECSManager& ecs, InputManager& input_manager, TextureManager* texture_manager, Camera* camera, Window* window) {
    std::unique_ptr<ClickSystem> click_system (new ClickSystem(&ecs, &input_manager, window, camera));
    ecs.register_system(std::move(click_system), 1);

    std::unique_ptr<PlayerMovementInputSystem> player_input_system (new PlayerMovementInputSystem(&ecs, &input_manager));
    ecs.register_system(std::move(player_input_system), 2);

    std::unique_ptr<PlayerAttackInputSystem> player_attack_input_system (new PlayerAttackInputSystem(&ecs, &input_manager));
    ecs.register_system(std::move(player_attack_input_system), 3);

    std::unique_ptr<MovementSystem> movement_system (new MovementSystem(&ecs));
    ecs.register_system(std::move(movement_system), 4);

    std::unique_ptr<CharacterUpdateSystem> character_update_system (new CharacterUpdateSystem(&ecs));
    ecs.register_system(std::move(character_update_system), 5);

    std::unique_ptr<SpriteAnimationSystem> sprite_animation_system (new SpriteAnimationSystem(&ecs));
    ecs.register_system(std::move(sprite_animation_system), 6);

    std::unique_ptr<SpriteRenderSystem> sprite_render_system (new SpriteRenderSystem(&ecs, texture_manager, camera, window));
    ecs.register_system(std::move(sprite_render_system), 7);
}
