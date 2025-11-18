#include "input_manager.h"


InputManager::InputManager() {
    m_keybinds[Action::WALK_UP] = SDLK_UP;
    m_keybinds[Action::WALK_DOWN] = SDLK_DOWN;
    m_keybinds[Action::WALK_LEFT] = SDLK_LEFT;
    m_keybinds[Action::WALK_RIGHT] = SDLK_RIGHT;

    m_keybinds[Action::ATTACK] = SDLK_f;
}


void InputManager::handle_input(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        SDL_Keycode key_code = e.key.keysym.sym;

        if (is_direction_key(key_code)) {
            m_pressed_direction_keys.erase(
                std::remove(m_pressed_direction_keys.begin(), m_pressed_direction_keys.end(), key_code), m_pressed_direction_keys.end()
            );
            m_pressed_direction_keys.insert(m_pressed_direction_keys.begin(), key_code);
        }

        m_keyboard_events.push_back({key_code, KeyboardEventType::BUTTONDOWN});
    }

    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        SDL_Keycode key_code = e.key.keysym.sym;

        if (is_direction_key(key_code)) {
            m_pressed_direction_keys.erase(
                std::remove(m_pressed_direction_keys.begin(), m_pressed_direction_keys.end(), key_code), m_pressed_direction_keys.end()
            );
        }

        m_keyboard_events.push_back({key_code, KeyboardEventType::BUTTONUP});
    }

    if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        SDL_MouseButtonEvent& m_event = e.button;

        MouseEvent mouse_event;
        mouse_event.x = m_event.x;
        mouse_event.y = m_event.y;
        mouse_event.type = e.type == SDL_MOUSEBUTTONDOWN ? MouseEventType::BUTTONDOWN : MouseEventType::BUTTONUP;
        mouse_event.button = m_event.button == SDL_BUTTON_LEFT ? MouseButton::LEFT : MouseButton::RIGHT;

        m_mouse_events.push_back(mouse_event);
    }
}


const std::vector<KeyboardEvent>& InputManager::get_keyboard_events() const {
    return m_keyboard_events;
}


const std::map<Action, SDL_Keycode>& InputManager::get_keybinds() const {
    return m_keybinds;
}


const std::vector<MouseEvent>& InputManager::get_mouse_events() const {
    return m_mouse_events;
}


void InputManager::flush_events() {
    flush_keyboard_events();
    flush_mouse_events();
}


void InputManager::flush_mouse_events() {
    m_mouse_events.clear();
}


void InputManager::flush_keyboard_events() {
    m_keyboard_events.clear();
}


const std::vector<SDL_Keycode>& InputManager::get_pressed_direction_keys() const {
    return m_pressed_direction_keys;
}


bool InputManager::is_direction_key(SDL_Keycode code) {
    return (
        code == m_keybinds[Action::WALK_DOWN]
        || code == m_keybinds[Action::WALK_UP]
        || code == m_keybinds[Action::WALK_LEFT]
        || code == m_keybinds[Action::WALK_RIGHT]
    );
}
