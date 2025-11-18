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


enum class KeyboardEventType {
    BUTTONDOWN = SDL_KEYDOWN,
    BUTTONUP = SDL_KEYUP
};


struct MouseEvent {
    // coordinates on the screen
    int x;
    int y;
    MouseButton button;
    MouseEventType type;
};


struct KeyboardEvent {
    SDL_Keycode key_code;
    KeyboardEventType type;
};


class InputManager {
public:
    InputManager();

    void handle_input(SDL_Event& e);

    const std::vector<KeyboardEvent>& get_keyboard_events() const;
    const std::map<Action, SDL_Keycode>& get_keybinds() const;
    const std::vector<MouseEvent>& get_mouse_events() const;

    void flush_mouse_events();
    void flush_keyboard_events();

    const std::vector<SDL_Keycode>& get_pressed_direction_keys() const;

private:
    std::vector<KeyboardEvent> m_keyboard_events;
    std::map<Action, SDL_Keycode> m_keybinds;
    std::vector<MouseEvent> m_mouse_events;
    
    std::vector<SDL_Keycode> m_pressed_direction_keys;
    bool is_direction_key(SDL_Keycode code);
};

#endif
