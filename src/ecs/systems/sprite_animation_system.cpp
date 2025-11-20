#include "sprite_animation_system.h"

#include "../components/sprite_animation.h"

#include "../managers/ecs_manager.h"


void SpriteAnimationSystem::update_entity(Entity& entity, Uint32 dt) {
    CharacterAnimation* _animation = m_ecs->get_component<CharacterAnimation>(entity);
    if (_animation == NULL) {
        return;
    }
    CharacterAnimation& animation = *_animation;

    animation.update_timer(dt);
}
