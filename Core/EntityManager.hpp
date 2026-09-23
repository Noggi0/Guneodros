#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "Entity.hpp"
#include <queue>
#include <stdexcept>

class EntityManager {
    public:
        EntityManager() {
            for (Entity ID = 0; ID < MAX_ENTITIES; ++ID)
                this->availableEntities.push(ID);
        };

        Entity createEntity() {
            if (this->availableEntities.empty())
                throw std::runtime_error("Too many entities");
            Entity ID = this->availableEntities.front();
            this->availableEntities.pop();
            this->aliveEntities.set(ID);
            return ID;
        };

        void destroyEntity(Entity ID) {
            if (!this->isAlive(ID))
                throw std::out_of_range("This entity does not exist");
            this->availableEntities.push(ID);
            this->aliveEntities.reset(ID);
        };

        bool isAlive(Entity ID) const {
            return ID < MAX_ENTITIES && this->aliveEntities[ID];
        };

        Entity getAliveEntities() const {
            return static_cast<Entity>(this->aliveEntities.count());
        };

    private:
        std::queue<Entity> availableEntities;
        std::bitset<MAX_ENTITIES> aliveEntities;
};

#endif /* !ENTITY_MANAGER_HPP */
