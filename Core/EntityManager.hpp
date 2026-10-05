#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "Entity.hpp"
#include <array>
#include <bitset>
#include <limits>
#include <queue>
#include <stdexcept>

class EntityManager {
    public:
        EntityManager() {
            for (std::size_t index = 0; index < MAX_ENTITIES; ++index)
                this->availableEntities.push(static_cast<EntityIndex>(index));
        };

        Entity createEntity() {
            if (this->availableEntities.empty())
                throw std::runtime_error("Too many entities");
            const EntityIndex index = this->availableEntities.front();
            this->availableEntities.pop();
            this->aliveEntities.set(index);
            return { index, this->generations[index] };
        };

        void destroyEntity(Entity entity) {
            if (!this->isAlive(entity))
                throw std::out_of_range("This entity does not exist");
            if (this->generations[entity.index] != std::numeric_limits<EntityGeneration>::max()) {
                this->availableEntities.push(entity.index);
                ++this->generations[entity.index];
            }
            this->aliveEntities.reset(entity.index);
        };

        bool isAlive(Entity entity) const noexcept {
            return entity.index < MAX_ENTITIES
                && this->aliveEntities[entity.index]
                && this->generations[entity.index] == entity.generation;
        };

        Entity getEntity(EntityIndex index) const {
            if (index >= MAX_ENTITIES || !this->aliveEntities[index])
                throw std::out_of_range("This entity does not exist");
            return { index, this->generations[index] };
        };

        std::size_t getAliveEntities() const {
            return this->aliveEntities.count();
        };

    private:
        std::queue<EntityIndex> availableEntities;
        std::bitset<MAX_ENTITIES> aliveEntities;
        std::array<EntityGeneration, MAX_ENTITIES> generations {};
};

#endif /* !ENTITY_MANAGER_HPP */
