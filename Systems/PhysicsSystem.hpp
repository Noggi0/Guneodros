#ifndef MOVEMENT_HPP_
#define MOVEMENT_HPP_

#include "./Systems.hpp"
#include "../Core/World.hpp"
#include "../Core/AABB.hpp"

class PhysicsSystem : public ISystem {
    public:
        PhysicsSystem() {
        };

        void update(World &world, float deltaTime) override {
            for (auto [EntityId, position, velocity, rigidbody] : world.view<Position, Velocity, Rigidbody>()) {
                auto previousPos = position;

                position.x += velocity.Vx * deltaTime;
                position.y += velocity.Vy * deltaTime;
                if (rigidbody.subjectToGravity)
                    velocity.Vy += gravity * deltaTime;

                auto *collider = world.tryGet<BoxCollider>(EntityId);
                if (!collider)
                    continue;

                // Check collisions
            }
        };

        ~PhysicsSystem() final = default;

    private:
        static constexpr float gravity = 9.81f;
};

#endif /* !MOVEMENT_HPP_ */
