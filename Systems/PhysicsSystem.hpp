#ifndef MOVEMENT_HPP_
#define MOVEMENT_HPP_

#include "./Systems.hpp"
#include "../Core/World.hpp"
#include "../Core/AABB.hpp"

class PhysicsSystem : public ISystem {
    public:
        PhysicsSystem() {
            this->signature.set(Components::TypeToID::Position);
            this->signature.set(Components::TypeToID::Velocity);
            this->signature.set(Components::TypeToID::Rigidbody);
        };

        void update(World &world, float deltaTime) override {
            for (const auto &entityID : this->entityList) {
                auto &Pos = world.get<Position>(entityID);
                auto &Vel = world.get<Velocity>(entityID);
                auto &Rb = world.get<Rigidbody>(entityID);
                auto *collider = world.tryGet<BoxCollider>(entityID);
                auto previousPos = Pos;

                Pos.x += Vel.Vx * deltaTime;
                Pos.y += Vel.Vy * deltaTime;
                if (Rb.subjectToGravity)
                    Vel.Vy += gravity * deltaTime;

                if (!collider)
                    continue;
                collider->x = Pos.x;
                collider->y = Pos.y;
                collider->triggered = false;

                for (const auto &otherID : this->entityList) {
                    if (entityID == otherID)
                        continue;
                    auto *secondCollider = world.tryGet<BoxCollider>(otherID);
                    if (secondCollider && aabb_collides(*collider, *secondCollider)) {
                        collider->triggered = true;
                        break;
                    }
                }

                if (collider->triggered) {
                    Pos = previousPos;
                    collider->x = Pos.x;
                    collider->y = Pos.y;
                }
            }
        };

        ~PhysicsSystem() final = default;

    private:
        static constexpr float gravity = 9.81f;
};

#endif /* !MOVEMENT_HPP_ */
