#include "utils.h"


bool check_collision(SDL_Rect& a, SDL_Rect& b) {

    // printf(
    //     "comparing SDL_Rect{%d, %d, %d, %d}\n", a.x, a.y, a.w, a.h
    // );

    int left_a = a.x;
    int right_a = a.x + a.w;
    int top_a = a.y;
    int bottom_a = a.y + a.h;

    int left_b = b.x;
    int right_b = b.x + b.w;
    int top_b = b.y;
    int bottom_b = b.y + b.h;

    if (bottom_a <= top_b) {
        return false;
    }

    if (top_a >= bottom_b) {
        return false;
    }

    if (right_a <= left_b) {
        return false;
    }

    if (left_a >= right_b) {
        return false;
    }

    return true;
}

bool check_collisions(SDL_Rect& a, std::vector<SDL_Rect*> other_colliders) {
    for (int i = 0; i < other_colliders.size(); i++) {
        if (check_collision(a, *other_colliders[i])) {
            return true;
        }
    }
    return false;
}
