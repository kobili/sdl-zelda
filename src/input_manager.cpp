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
}
