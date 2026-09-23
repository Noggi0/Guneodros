#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include "WindowManager.hpp"
#include "InputManager.hpp"
#include "World.hpp"
#include <chrono>
#include <functional>

class Application {
    public:
        Application(const std::string &title = "Guneodros", int width = 800,
                    int height = 600, bool resizable = true) {
            this->windowMgr.createWindow(title, width, height, resizable);
            this->inputMgr.registerWindow(this->windowMgr.getWindow());
        };

        World &getWorld() {
            return this->world;
        };

        const InputManager &getInput() const {
            return this->inputMgr;
        };

        SDL_Window *getWindow() const {
            return this->windowMgr.getWindow();
        };

        // The optional callback runs after input polling, before the systems.
        void run(const std::function<void(float)> &onUpdate = {}) {
            auto elapsed = std::chrono::steady_clock::now();
            this->isRunning = true;
            while (this->isRunning) {
                this->inputMgr.update();
                if (this->inputMgr.getCloseEvent()) {
                    this->stop();
                    break;
                }
                auto now = std::chrono::steady_clock::now();
                float deltaTime = std::chrono::duration<float>(now - elapsed).count();
                elapsed = now;
                if (onUpdate)
                    onUpdate(deltaTime);
                if (this->isRunning)
                    this->world.update(deltaTime);
                float frameTime = std::chrono::duration<float>(
                    std::chrono::steady_clock::now() - now).count();
                if (this->isRunning && frameTime < this->clock)
                    SDL_Delay(static_cast<Uint32>((this->clock - frameTime) * 1000));
            }
        };

        void stop() {
            this->isRunning = false;
        };

        Application(const Application&) = delete;
        Application &operator=(const Application&) = delete;

    private:
        WindowManager windowMgr;
        InputManager inputMgr;
        World world;
        float clock = 1 / 60.0f;
        bool isRunning = false;
};

#endif /* !APPLICATION_HPP */
