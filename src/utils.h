#ifndef UTILS_H
#define UTILS_H

#include "SDL.h"
#include <vector>

/*
* Check if rectangle A collides with rectangle B
*/
bool check_collision(SDL_Rect& a, SDL_Rect& b);


bool check_collisions(SDL_Rect& a, std::vector<SDL_Rect*> other_colliders);

#endif
