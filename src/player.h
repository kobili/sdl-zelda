#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "entity.h"

const int DEFAULT_VELOCITY = 1;


/**
 * The overworld map is arranged in a 16x8 grid of 256x176 screens.
 * 
 * This struct describes a zone in the overworld by encoding the
 * column and row of the zone in the grid.
 */
struct Zone {
    int col;
    int row;
};


class Player : public Entity {
public:
    using Entity::Entity;

    void handle_event(SDL_Event& e);

    void move(std::vector<SDL_Rect*> colliders) override;

    Zone get_current_zone();
};

#endif
