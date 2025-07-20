#ifndef __INPUT_MANAGER_HPP__
#define __INPUT_MANAGER_HPP__

#include "../Utils/types.hpp"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>
#include <bitset>

class InputManager {
    public:
        InputManager() {
        };
        void update() {
            this->previous_keyboard_state = this->keyboard_state;
            //this->keyboard_state = 0;
            while (SDL_PollEvent(&this->event)) {
                switch (this->event.type) {
                    case SDL_QUIT:
                        this->closeEvent = true;
                        break;
                    case SDL_KEYUP:
                    case SDL_KEYDOWN:
                        this->keyboard_state[this->event.key.keysym.scancode] = this->event.type == SDL_KEYDOWN;
                    default:
                        break;
                }
            }
        }
        const bool getCloseEvent() const {
            return this->closeEvent;
        }
        void registerWindow(SDL_Window *window) {
            this->window = window;
        };
        const bool isKeyPressed(char *x) const {
            return keyboard_state[SDL_GetScancodeFromName(x)];
        }
        const bool isKeyReleased(char *x) const
        {
            return !keyboard_state[SDL_GetScancodeFromName(x)] && previous_keyboard_state[SDL_GetScancodeFromName(x)];
        }
        const Vec2<int> getMousePosition() const {
            Vec2<int> mousePosition;
            SDL_GetMouseState(&mousePosition._x, &mousePosition._y);
            return mousePosition;
        }
        ~InputManager() {

        };
    private:
        // Create an associative array corresponding to a "virtual" keyboard,
        // so we can keep track of multiple presses at once.
        // const Uint8 *keyboard_state;

        std::bitset<256> previous_keyboard_state;
        std::bitset<256> keyboard_state;
        SDL_Window *window;
        SDL_Event event;
        bool closeEvent = false;
};

#endif /* __INPUT_MANAGER_HPP__ */
