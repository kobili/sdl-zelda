#include "animation_system.h"

#include "../components/sprite_animation.h"

#include "../managers/ecs_manager.h"


void AnimationSystem::update_entity(Entity& entity, Uint32 dt) {
    SpriteAnimation* _animation = m_ecs->get_component<SpriteAnimation>(entity);
    if (_animation == NULL) {
        return;
    }
    SpriteAnimation& animation = *_animation;

    if (!animation.is_animating()) {
        return;
    }

    animation.update_timer(dt);
}
