#include "../Core/Application.hpp"
#include "../Systems/SpriteRenderer.hpp"
#include <iostream>

int main() {
    {
        Application app("Guneodros lifecycle test", 320, 240, false);
        app.getWorld().addSystem<SpriteRenderer>(app.getWindow());
        int frames = 0;
        app.run([&frames](float) {
            ++frames;
            SDL_Event event{};
            event.type = SDL_QUIT;
            if (SDL_PushEvent(&event) != 1)
                throw std::runtime_error("Could not queue quit event");
        });
        if (frames != 1)
            throw std::runtime_error("Application did not stop on SDL_QUIT");
    }
    {
        Application app("Guneodros stop test", 320, 240, false);
        app.run([&app](float) { app.stop(); });
    }
    std::cout << "Application tests passed" << std::endl;
}
