#include "Core/Application.hpp"
#include "Core/Logger.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/SpriteRenderer.hpp"
#include "Utils/types.hpp"

int main() {
    Application app("Testing Guneodros -- MAIN");
    World &world = app.getWorld();

    for (std::size_t i = 0; i < MAX_ENTITIES; ++i) {
        Entity entity = world.createEntity();
        world.emplace<Position>(entity);
        world.emplace<Velocity>(entity, 0.0, -1.0, 0.0);
        world.emplace<Rigidbody>(entity);
    }

    world.addSystem<PhysicsSystem>();
    world.addSystem<SpriteRenderer>(app.getWindow());
    Logger::logInfo("Filled");

    app.run([&app](float) {
        if (app.getInput().isKeyPressed("b"))
            Logger::logInfo("B pressed");
    });
}
