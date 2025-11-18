#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <map>
#include <vector>
#include "SDL.h"


enum Action {
    WALK_UP,
    WALK_DOWN,
    WALK_LEFT,
    WALK_RIGHT,
    ATTACK
};


class InputManager {
public:
    InputManager();

    void handle_input(SDL_Event& e);

private:
    std::map<Action, SDL_Keycode> m_keybinds;
    std::vector<SDL_Keycode> m_pressed_keys;
};

#endif
