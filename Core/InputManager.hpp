#include "./EntityManager.hpp"
#include "../Utils/types.hpp"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mouse.h>

class InputManager {
    public:
        InputManager() {
            this->keyboard_state = SDL_GetKeyboardState(nullptr);
        };
        void update() {
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        this->closeEvent = true;
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
        const Uint8 *keyboard_state;

        SDL_Window *window;
        bool closeEvent = false;
};