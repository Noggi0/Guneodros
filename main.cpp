#include "./Core/Entity.hpp"
#include "./Core/EntityManager.hpp"
#include "Components/Component.hpp"
#include "./Core/SystemManager.hpp"
#include "Systems/Systems.hpp"
#include "Systems/Movement.hpp"

EntityManager Engine;

/*int main(void)
{
    Position pos;
    std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
}*/

int main () {
    Movement mvt;
    Engine.registerSystem(&mvt);
    std::vector<Entity> entities(MAX_ENTITES);
    for (auto entity : entities) {
        entity = Engine.NewEntity();
        Position pos;
        Velocity vel;
        Rigidbody rb;
        Engine.AddComponent(entity, &pos);
        Engine.AddComponent(entity, &vel);
        Engine.AddComponent(entity, &rb);
        vel.Vy = -1.0;
    }
    std::cout << "filled" << std::endl;
    Engine.createWindow("Testing Guneodros", 800, 600, true);
    while (Engine.isRunning) {
        Engine.update();
        if (Engine.isKeyPressed("b")) {
            std::cout << "B IS PRESSED" << std::endl;
        }
    }
}