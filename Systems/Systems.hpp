#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "../Core/Entity.hpp"
#include <vector>
#include <list>
#include <algorithm>
#include <string>

class World;

class ISystem {
        public:
            virtual void update(World &world, float deltaTime) = 0;
            virtual ~ISystem() = default;
};

#endif /* !SYSTEMS_HPP */
