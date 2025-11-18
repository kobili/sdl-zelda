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

        m_pressed_keys.erase(
            std::remove(m_pressed_keys.begin(), m_pressed_keys.end(), key_code), m_pressed_keys.end()
        );
        m_pressed_keys.insert(m_pressed_keys.begin(), key_code);
    }

    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        SDL_Keycode key_code = e.key.keysym.sym;

        m_pressed_keys.erase(
            std::remove(m_pressed_keys.begin(), m_pressed_keys.end(), key_code), m_pressed_keys.end()
        );
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


const std::vector<SDL_Keycode>& InputManager::get_pressed_keys() const {
    return m_pressed_keys;
}


const std::map<Action, SDL_Keycode>& InputManager::get_keybinds() const {
    return m_keybinds;
}

const std::vector<MouseEvent>& InputManager::get_mouse_events() const {
    return m_mouse_events;
}

void InputManager::flush_mouse_events() {
    m_mouse_events.clear();
}
