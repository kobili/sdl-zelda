#include "ecs_manager.h"

ECSManager::ECSManager() {

}


void ECSManager::add_position(Entity entity, std::unique_ptr<Position> position) {
    m_positions[entity.get_id()] = std::move(position);
}


Position* ECSManager::get_position(Entity entity) {
    if (m_positions.find(entity.get_id()) == m_positions.end()) {
        return NULL;
    }

    return m_positions[entity.get_id()].get();
}


void ECSManager::add_sprite(Entity entity, std::unique_ptr<Sprite> sprite) {
    m_sprites[entity.get_id()] = std::move(sprite);
}


Sprite* ECSManager::get_sprite(Entity entity) {
    if (m_sprites.find(entity.get_id()) == m_sprites.end()) {
        return NULL;
    }

    return m_sprites[entity.get_id()].get();
}
