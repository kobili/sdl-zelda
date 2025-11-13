#ifndef ECS_MANAGER_H
#define ECS_MANAGER_H


#include <map>
#include <memory>

#include "entity.h"
#include "components/position.h"
#include "components/sprite.h"


class ECSManager {
public:
    ECSManager();

    void add_position(Entity entity, std::unique_ptr<Position>);
    Position* get_position(Entity entity);

    void add_sprite(Entity entity, std::unique_ptr<Sprite>);
    Sprite* get_sprite(Entity entity);

private:
    std::map<int, std::unique_ptr<Position>> m_positions;
    std::map<int, std::unique_ptr<Sprite>> m_sprites;
};

#endif
