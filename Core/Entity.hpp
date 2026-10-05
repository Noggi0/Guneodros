#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <compare>
#include <cstddef>
#include <cstdint>
#include <limits>

using EntityIndex = std::uint16_t;
using EntityGeneration = std::uint32_t;

constexpr std::size_t MAX_ENTITIES = 10000;
constexpr EntityIndex INVALID_ENTITY_INDEX = static_cast<EntityIndex>(MAX_ENTITIES);

static_assert(MAX_ENTITIES < std::numeric_limits<EntityIndex>::max());

struct Entity {
    EntityIndex index = INVALID_ENTITY_INDEX;
    EntityGeneration generation = 0;

    bool operator==(const Entity &other) const = default;
    auto operator<=>(const Entity &other) const = default;
};

#endif /* !ENTITY_HPP */
