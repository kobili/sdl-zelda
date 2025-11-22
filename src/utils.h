#ifndef UTILS_H
#define UTILS_H

#include "SDL.h"
#include <vector>
#include <typeindex>

/*
* Check if rectangle A collides with rectangle B
*/
bool check_collision(SDL_Rect& a, SDL_Rect& b);


bool check_collisions(SDL_Rect& a, std::vector<SDL_Rect*> other_colliders);


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

template <typename T>
std::type_index get_type_index() {
    return std::type_index(typeid(T));
}

#endif
