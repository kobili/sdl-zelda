#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "entity.h"

const int DEFAULT_VELOCITY = 1;


class Player : public Entity {
public:
    using Entity::Entity;

    void handle_event(SDL_Event& e);

    void move(std::vector<SDL_Rect*> colliders) override;
};

#endif
