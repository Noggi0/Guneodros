#include "./EntityManager.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <exception>

class WindowManager {
    public:
        WindowManager() {
            SDL_Init(SDL_INIT_VIDEO);
            this->window = nullptr;
        };
        /**
         * Create a new Window.
         * If a window already exists, the function throws an error.
         * 
         * @param title string containing the name of the window
         * @param width width of the window
         * @param height height of the window
         */
        void createWindow(std::string title, int width, int height, bool resizable) {
            if (this->window != nullptr)
                return;
            this->window = SDL_CreateWindow(title.c_str(),
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            width,
                                            height,
                                            (resizable ? SDL_WINDOW_RESIZABLE : 0) | SDL_WINDOW_SHOWN);
            if (!window) {
                throw std::string("Could not create SDL Window.") + SDL_GetError();
            }
        };
        SDL_Window *getWindow() const {
            return this->window;
        }
        bool isWindowFocused() const {
            return SDL_GetWindowFlags(this->window) & SDL_WINDOW_INPUT_FOCUS;
        };
        ~WindowManager() {
            SDL_DestroyWindow(this->window);
            SDL_Quit();
        };
    private:
        SDL_Window *window;
};
