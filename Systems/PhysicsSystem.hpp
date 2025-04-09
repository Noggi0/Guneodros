#ifndef MOVEMENT_HPP_
#define MOVEMENT_HPP_

#include "./Systems.hpp"
#include "../Core/EntityManager.hpp"
#include "../Core/AABB.hpp"

/**
 **
 ** This system's gonna override the updateEntityList function
 ** because we wanna keep track of some entities that have non-mandatory components.
 **
 **/

extern EntityManager Engine;

class PhysicsSystem : public ISystem {
    public:
        PhysicsSystem() {
            this->signature.set(Components::TypeToID::Position);
            this->signature.set(Components::TypeToID::Velocity);
            this->signature.set(Components::TypeToID::Rigidbody);
        };
        void updateEntityList(Entity ID, const Signature& entitySignature) override
        {
            auto it = std::find(this->entityList.begin(), this->entityList.end(), ID);
            // Entity doesn't exist in EntityList
            if (it == this->entityList.end()) {
                // Entity matches the requirements for the System ==> add
                if ((entitySignature & this->signature) == this->signature)
                {
                    std::cout << "Matches requirements:" << ID << std::endl;
                    std::cout << "Entity Signature:" << entitySignature << std::endl;
                    std::cout << "System Signature:" << this->signature << std::endl;

                    this->entityList.push_back(ID);
                    if (entitySignature[Components::TypeToID::BoxCollider])
                    {
                        collidersList.push_back(ID);
                        std::cout << "added in collidersList:" << ID << std::endl;
                    }
                }
            } else {
                // Entity is in EntityList and doesn't match the requirements for the System anymore ==> delete
                if ((entitySignature & this->signature) != this->signature)
                {
                    auto colliderIt = std::find(this->collidersList.begin(), this->collidersList.end(), ID);
                    if (colliderIt != this->collidersList.end())
                    {
                        this->collidersList.erase(colliderIt);
                        std::cout << "erased from collidersList:" << ID << std::endl;

                    }
                    this->entityList.erase(it);
                } else { // still matches the signature, just has new components
                    if (entitySignature[Components::TypeToID::BoxCollider])
                    {
                        collidersList.push_back(ID);
                        std::cout << "added in collidersList:" << ID << std::endl;
                    }
                }
            }
        };
        void update() override {
            const float deltaTime = Engine.getDeltaTime();
            for (const auto &entityID : this->entityList) {
                auto &Pos = Engine.getComponent<Position>(entityID, Components::TypeToID::Position);
                auto &Vel = Engine.getComponent<Velocity>(entityID, Components::TypeToID::Velocity);
                auto &Rb = Engine.getComponent<Rigidbody>(entityID, Components::TypeToID::Rigidbody);
                auto &collider = Engine.getComponent<BoxCollider>(entityID, Components::TypeToID::BoxCollider);

                auto previousPos = Pos;

                Pos.x += Vel.Vx * deltaTime;
                Pos.y += Vel.Vy * deltaTime;
                collider.x = Pos.x;
                collider.y = Pos.y;
                
                if (Rb.subjectToGravity)
                    Vel.Vy += gravity * deltaTime;

                for (const auto &otherID : this->entityList)
                {
                    if (entityID == otherID)
                        continue;

                    auto &secondCollider = Engine.getComponent<BoxCollider>(otherID, Components::TypeToID::BoxCollider);

                    if (aabb_collides(collider, secondCollider))
                        collider.triggered = true;
                    else
                        collider.triggered = false;
                }

                if (collider.triggered)
                {
                    Pos = previousPos;
                    collider.x = Pos.x;
                    collider.y = Pos.y;
                }

            }
        };
        ~PhysicsSystem() final = default;

    private:
        static constexpr float gravity = 9.81f;
        std::vector<Entity> collidersList;

};

#endif /* !MOVEMENT_HPP_ */
