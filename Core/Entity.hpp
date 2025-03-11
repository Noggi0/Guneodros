#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <stdint.h>
#include <iostream>
#include <bitset>

using Entity = std::uint16_t;
constexpr Entity MAX_ENTITIES = 10000;

using ComponentType = std::uint8_t;
constexpr ComponentType MAX_COMPONENT = 32;

using Signature = std::bitset<MAX_COMPONENT>;

namespace Components {
    enum TypeToID {
        Crashed = -1,
        Position = 0,
        Velocity = 1,
        Rotation = 2,
        Rigidbody = 3,
        Sprite = 4,
        Model3D = 5,
        Camera = 6,
        Character = 7
    };
}

#endif /* !ENTITY_HPP */