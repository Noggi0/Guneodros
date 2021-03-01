/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main
*/

#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Component.hpp"
#include "SystemManager.hpp"
#include "Systems.hpp"
#include "Movement.hpp"

EntityManager EM;

int main (int ac, char **av) {
    Movement mvt;
    EM.registerSystem(&mvt);
    std::vector<Entity> entities(MAX_ENTITES);
    for (auto entity : entities) {
        entity = EM.NewEntity();
        Position pos;
        Velocity vel;
        EM.AddComponent(entity, &pos);
        EM.AddComponent(entity, &vel);
        vel.Vy = -1.0;
    }
    std::cout << "filled" << std::endl;
    for (int i = 0; i < 100000; i++) {
        EM.update();
    }
}