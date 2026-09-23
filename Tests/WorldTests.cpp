#include "../Core/World.hpp"
#include "../Systems/PhysicsSystem.hpp"
#include <iostream>

void require(bool condition) {
    if (!condition)
        throw std::runtime_error("World test failed");
}

class PositionSystem : public ISystem {
    public:
        PositionSystem() {
            this->signature.set(Components::TypeToID::Position);
        };
        void update(World &world, float deltaTime) override {
            for (Entity ID : this->entityList)
                world.get<Position>(ID).x += deltaTime;
        };
        std::size_t size() const {
            return this->entityList.size();
        };
};

class OwnedComponent : public IComponent {
    public:
        explicit OwnedComponent(int &destroyed) : destroyed(destroyed) {
            this->id = 6;
        };
        ~OwnedComponent() {
            ++this->destroyed;
        };
    private:
        int &destroyed;
};

int main() {
    int destroyed = 0;
    {
        World world;
        Entity first = world.createEntity();
        Entity second = world.createEntity();
        world.emplace<Position>(first, 1.0f);
        world.emplace<Position>(second, 10.0f);
        world.emplace<OwnedComponent>(first, destroyed);
        auto &system = world.addSystem<PositionSystem>();
        require(system.size() == 2);
        world.update(0.5f);
        require(world.get<Position>(first).x == 1.5f);

        bool duplicateRejected = false;
        try {
            world.emplace<Position>(first);
        } catch (const std::logic_error&) {
            duplicateRejected = true;
        }
        require(duplicateRejected && system.size() == 2);
        world.remove<Position>(first);
        require(!world.has<Position>(first) && system.size() == 1);
        require(world.tryGet<Position>(first) == nullptr);
        bool missingRejected = false;
        try {
            world.get<Position>(first);
        } catch (const std::out_of_range&) {
            missingRejected = true;
        }
        require(missingRejected);
        world.emplace<Position>(first);
        require(system.size() == 2);
        world.destroyEntity(first);
        require(destroyed == 1 && system.size() == 1);
        world.update(1.0f);
        require(world.get<Position>(second).x == 11.5f);
        require(world.getAliveEntities() == 1);

        bool invalidRejected = false;
        try {
            world.destroyEntity(first);
        } catch (const std::out_of_range&) {
            invalidRejected = true;
        }
        require(invalidRejected && world.getAliveEntities() == 1);
        world.emplace<OwnedComponent>(second, destroyed);
        const World &readOnly = world;
        require(readOnly.get<Position>(second).x == 11.5f);

        World independent;
        Entity other = independent.createEntity();
        independent.emplace<Position>(other);
        independent.emplace<Velocity>(other, 2.0, 0.0, 0.0);
        independent.emplace<Rigidbody>(other, false);
        independent.addSystem<PhysicsSystem>();
        independent.update(0.5f);
        require(independent.get<Position>(other).x == 1.0f);
        require(world.get<Position>(second).x == 11.5f);
    }
    require(destroyed == 2);

    EntityManager entities;
    Entity first = entities.createEntity();
    for (Entity i = 1; i < MAX_ENTITIES; ++i)
        entities.createEntity();
    bool capacityRejected = false;
    try {
        entities.createEntity();
    } catch (const std::runtime_error&) {
        capacityRejected = true;
    }
    require(capacityRejected);
    entities.destroyEntity(first);
    require(entities.createEntity() == first);
    std::cout << "World tests passed" << std::endl;
}
