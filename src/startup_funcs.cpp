#include "startup_funcs.h"

#include "constants.h"

#include "ecs/components/position.h"
#include "ecs/components/velocity.h"
#include "ecs/components/moveable.h"
#include "ecs/components/player.h"
#include "ecs/components/enemy.h"
#include "ecs/components/collider.h"
#include "ecs/components/clickable.h"
#include "ecs/components/sprite_animation.h"
#include "ecs/components/character.h"
#include "ecs/components/entity_lifetime.h"
#include "ecs/components/invincibility.h"

#include "ecs/systems/click_system.h"
#include "ecs/systems/movement_system.h"
#include "ecs/systems/player_movement_input.h"
#include "ecs/systems/sprite_renderer.h"
#include "ecs/systems/sprite_animation_system.h"
#include "ecs/systems/player_attack_input.h"
#include "ecs/systems/character_update.h"
#include "ecs/systems/entity_lifetime_system.h"
#include "ecs/systems/sword_animation.h"
#include "ecs/systems/hurtbox_system.h"
#include "ecs/systems/collider_system.h"


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


CharacterAnimation load_player_animations() {
    CharacterAnimation animation = CharacterAnimation(SpriteInformation{"resources/sprites/link.png", 16, 16});

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
        true,
        {idle_up_frames, idle_down_frames, idle_left_frames, idle_right_frames}
    };

    animation.set_animation_set(CharacterState::IDLE, idle_animation_set);

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
        true,
        {move_up_frames, move_down_frames, move_left_frames, move_right_frames}
    };

    animation.set_animation_set(CharacterState::MOVING, movement_animation_set);


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
        false,
        {attack_up_frames, attack_down_frames, attack_left_frames, attack_right_frames}
    };

    animation.set_animation_set(CharacterState::ATTACKING, attack_animation_set);

    return animation;
}


void player_callback(ECSManager& ecs, int entity_id) {
    Position& player_position = *ecs.get_component<Position>(entity_id);
    printf("Player with id %d at (%f, %f)\n", entity_id, player_position.get_x(), player_position.get_y());
}


void load_player(ECSManager& ecs) {
    Uint32 player = ecs.create_entity_id();
    ecs.add_entity(player);

    Character character = Character(Direction::DOWN, CharacterState::IDLE, LINK_ATTACK_DURATION_MS);
    ecs.add_component(player, character);

    Position position = Position(
        (7 * NES_SCREEN_WIDTH + NES_SCREEN_WIDTH / 2) - 16,
        7 * NES_SCREEN_HEIGHT + NES_SCREEN_HEIGHT / 2
    );
    if (ecs.add_component<Position>(player, position) == NULL) {
        printf("failed to add Position for player\n");
        return;
    }

    if (ecs.add_component<Velocity>(player, Velocity()) == NULL) {
        printf("failed to add Velocity for player\n");
        return;
    }

    if (ecs.add_component<Movable>(player, Movable()) == NULL) {
        printf("failed to add Movable for player\n");
        return;
    }

    if (ecs.add_component<Player>(player, Player()) == NULL) {
        printf("failed to load player component for player\n");
        return;
    }

    Collider collider = Collider(
        (7 * NES_SCREEN_WIDTH + NES_SCREEN_WIDTH / 2) - 16,
        7 * NES_SCREEN_HEIGHT + NES_SCREEN_HEIGHT / 2
        ,
        16,
        16
    );
    if (ecs.add_component<Collider>(player, collider) == NULL) {
        printf("failed to load collider for player\n");
        return;
    }

    ClickHandler on_click = [&ecs](int entity_id) {
        player_callback(ecs, entity_id);
    };

    if (ecs.add_component<Clickable>(player, Clickable(on_click)) == NULL) {
        printf("failed to load clickable for player\n");
    }

    auto animation = load_player_animations();
    if (ecs.add_component<CharacterAnimation>(player, std::move(animation)) == NULL) {
        printf("failed to load player animations");
    }

    load_sword_attack_animation(ecs, player);
}


CharacterAnimation load_enemy_animation() {
    CharacterAnimation animation = CharacterAnimation(SpriteInformation{"resources/sprites/oktorok__red.png", 16, 16});

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
        false,
        {
            idle_up_frames, idle_down_frames, idle_left_frames, idle_right_frames
        }
    };

    animation.set_animation_set(CharacterState::IDLE, idle_set);

    return animation;
}


void load_enemy(ECSManager& ecs) {
    int enemy = ecs.create_entity_id();
    ecs.add_entity(enemy);

    Character character = Character(Direction::LEFT, CharacterState::IDLE);
    ecs.add_component(enemy, std::move(character));

    ecs.add_component(enemy, Enemy());

    Position position = Position(
        7 * NES_SCREEN_WIDTH + NES_SCREEN_WIDTH / 2,
        7 * NES_SCREEN_HEIGHT + NES_SCREEN_HEIGHT / 2
    );
    if (ecs.add_component<Position>(enemy, position) == NULL) {
        printf("failed to add Position for enemy\n");
        return;
    }

    if (ecs.add_component<Velocity>(enemy, Velocity()) == NULL) {
        printf("failed to add Velocity for enemy\n");
        return;
    }

    Collider collider = Collider(
        7 * NES_SCREEN_WIDTH + NES_SCREEN_WIDTH / 2,
        7 * NES_SCREEN_HEIGHT + NES_SCREEN_HEIGHT / 2,
        16,
        16,
        ColliderType::EPHEMERAL
    );
    if (ecs.add_component<Collider>(enemy, collider) == NULL) {
        printf("failed to load collider for enemy\n");
        return;
    }

    ecs.add_component<Hurtbox>(enemy, Hurtbox(3));

    ClickHandler on_click = [&ecs](Uint32 entity_id) {
        printf("I'm so hungry, I could eat an oktorok!\n");
        // ecs.mark_remove(entity_id);
        ecs.add_component<Invincibility>(entity_id, Invincibility(5000));
    };

    if (ecs.add_component<Clickable>(enemy, Clickable(on_click)) == NULL) {
        printf("failed to load clickable for enemy\n");
        return;
    }

    if (ecs.add_component<CharacterAnimation>(enemy, load_enemy_animation()) == NULL) {
        printf("failed to load animation for enemy.\n");
        return;
    }
}


void load_sword_attack_animation(ECSManager& ecs, int player_entity) {
    // load animations
    std::vector<AnimationFrameData> attack_up_frames = {
        {0, 0, false, false, 3, -12},
        {0, 0, false, false, 3, -12},
        {0, 0, false, false, 3, -11},
        {0, 0, false, false, 3, -3},
    };
    std::vector<AnimationFrameData>  attack_down_frames = {
        {-1, -1, false, true, 0, 0},
        {0, 0, false, true, 5, 11},
        {0, 0, false, true, 5, 7},
        {0, 0, false, true, 5, 3},
    };
    std::vector<AnimationFrameData> attack_left_frames = {
        {-1, -1, true, false, -12, 1},
        {1, 0, true, false, -12, 1},
        {1, 0, true, false, -8, 1},
        {1, 0, true, false, -4, 1}
    };
    std::vector<AnimationFrameData> attack_right_frames = {
        {-1, -1, false, false, 12, 1},
        {1, 0, false, false, 12, 1},
        {1, 0, false, false, 8, 1},
        {1, 0, false, false, 4, 1}
    };

    SwordAnimation animation = (
        SwordAnimation(
            {"resources/sprites/wood_sword_sprites.png", 16, 16},
            {
                LINK_ATTACK_ANIMATION_FRAME_DURATION_MS,
                false,
                {
                    attack_up_frames, attack_down_frames, attack_left_frames, attack_right_frames
                }
            }
        )
    );

    ecs.add_component<SwordAnimation>(player_entity, std::move(animation));
}


void load_systems(ECSManager& ecs, InputManager& input_manager, TextureManager* texture_manager, Camera* camera, Window* window) {
    std::unique_ptr<ClickSystem> click_system (new ClickSystem(&ecs, &input_manager, window, camera));
    ecs.register_system(std::move(click_system));

    std::unique_ptr<PlayerMovementInputSystem> player_input_system (new PlayerMovementInputSystem(&ecs, &input_manager));
    ecs.register_system(std::move(player_input_system));

    std::unique_ptr<PlayerAttackInputSystem> player_attack_input_system (new PlayerAttackInputSystem(&ecs, &input_manager));
    ecs.register_system(std::move(player_attack_input_system));

    std::unique_ptr<MovementSystem> movement_system (new MovementSystem(&ecs));
    ecs.register_system(std::move(movement_system));

    std::unique_ptr<CharacterUpdateSystem> character_update_system (new CharacterUpdateSystem(&ecs));
    ecs.register_system(std::move(character_update_system));

    std::unique_ptr<AttackDamageDetectionSystem> damage_detection_system (new AttackDamageDetectionSystem(&ecs));
    ecs.register_system(std::move(damage_detection_system));

    std::unique_ptr<SpriteAnimationSystem> sprite_animation_system (new SpriteAnimationSystem(&ecs));
    ecs.register_system(std::move(sprite_animation_system));

    std::unique_ptr<EnemySpriteRenderSystem> enemy_render_system (new EnemySpriteRenderSystem(&ecs, texture_manager, camera, window));
    ecs.register_system(std::move(enemy_render_system));

    std::unique_ptr<SwordAnimationSystem> sword_animation_system (new SwordAnimationSystem(&ecs, texture_manager, camera, window));
    ecs.register_system(std::move(sword_animation_system));

    std::unique_ptr<PlayerSpriteRenderSystem> player_render_system (new PlayerSpriteRenderSystem(&ecs, texture_manager, camera, window));
    ecs.register_system(std::move(player_render_system));

    std::unique_ptr<EntityLifetimeSystem> entity_lifetime_system (new EntityLifetimeSystem(&ecs));
    ecs.register_system(std::move(entity_lifetime_system));

    std::unique_ptr<InvincibilityLifetimeSystem> invincibility_lifetime_system (new InvincibilityLifetimeSystem(&ecs));
    ecs.register_system(std::move(invincibility_lifetime_system));

    std::unique_ptr<AttackHurtboxIncrementSystem> hurtbox_increment_system (new AttackHurtboxIncrementSystem(&ecs));
    ecs.register_system(std::move(hurtbox_increment_system));

    std::unique_ptr<ColliderDebugRenderSystem> collider_debug_render_system (new ColliderDebugRenderSystem(&ecs, camera, window));
    ecs.register_system(std::move(collider_debug_render_system));
}
