#include "./Core/Entity.hpp"
#include "./Core/EntityManager.hpp"
#include "Components/Component.hpp"
#include "Systems/Systems.hpp"
#include "Systems/Movement.hpp"
#include "Systems/Render.hpp"
#include "./Core/Logger.hpp"

EntityManager Engine;

/*int main(void)
{
    Position pos;
    std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
}*/

int main () {
    Movement mvt;
    Engine.registerSystem(&mvt);
    std::vector<Entity> entities(MAX_ENTITIES);
    for (auto& entity : entities) {
        entity = Engine.newEntity();
        Position pos;
        Velocity vel;
        Rigidbody rb;
        Engine.addComponent(entity, &pos);
        Engine.addComponent(entity, &vel);
        Engine.addComponent(entity, &rb);
        vel.Vy = -1.0;
    }
    Logger::logInfo("Filled");
    Engine.createWindow("Testing Guneodros", 800, 600, true);
    while (Engine.isRunning) {
        Engine.update();
        if (Engine.isKeyPressed("b")) {
            Logger::logInfo("B pressed");
        }
    }
}