#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <map>
#include <vector>
#include <queue>
#include "SDL.h"


enum class Action {
    WALK_UP,
    WALK_DOWN,
    WALK_LEFT,
    WALK_RIGHT,
    ATTACK
};


enum class MouseButton {
    LEFT,
    RIGHT
};


enum class MouseEventType {
    BUTTONDOWN = SDL_MOUSEBUTTONDOWN,
    BUTTONUP = SDL_MOUSEBUTTONUP
};


struct MouseEvent {
    // coordinates on the screen
    int x;
    int y;
    MouseButton button;
    MouseEventType type;
};


class InputManager {
public:
    InputManager();

    void handle_input(SDL_Event& e);

    const std::vector<SDL_Keycode>& get_pressed_keys() const;
    const std::map<Action, SDL_Keycode>& get_keybinds() const;
    const std::vector<MouseEvent>& get_mouse_events() const;

    void flush_mouse_events();

private:
    std::map<Action, SDL_Keycode> m_keybinds;
    std::vector<SDL_Keycode> m_pressed_keys;

    std::vector<MouseEvent> m_mouse_events;
};

#endif
