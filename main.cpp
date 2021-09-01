/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main
*/

#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Components/Component.hpp"
#include "Systems/SystemManager.hpp"
#include "Systems/Systems.hpp"
#include "Systems/Movement.hpp"
#include "Utils/types.hpp"

EntityManager EM;

/*int main(void)
{
    Position pos;
    std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
}*/

int main () {
    Vec3<int> intV;
    Movement mvt;
    EM.registerSystem(&mvt);
    std::vector<Entity> entities(MAX_ENTITES);
    for (auto entity : entities) {
        entity = EM.NewEntity();
        Position pos;
        Velocity vel;
        Rigidbody rb;
        EM.AddComponent(entity, &pos);
        EM.AddComponent(entity, &vel);
        EM.AddComponent(entity, &rb);
        vel.Vy = -1.0;
    }
    std::cout << "filled" << std::endl;
    for (uint64_t i = 0; i < UINT16_MAX; i++) {
        EM.update();
    }
}
