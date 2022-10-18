#ifndef MOVEMENT_HPP_
#define MOVEMENT_HPP_

#include "./Systems.hpp"
#include "../Core/EntityManager.hpp"

extern EntityManager Engine;

class Movement : public ISystem {
    public:
        Movement() {
            this->signature.set(Components::TypeToID::Position);
            this->signature.set(Components::TypeToID::Velocity);
            this->signature.set(Components::TypeToID::Rigidbody);
        };
        void update() {
            for (auto &entityID : this->entityList) {
                auto &Pos = Engine.getComponent<Position>(entityID, Components::TypeToID::Position);
                auto &Vel = Engine.getComponent<Velocity>(entityID, Components::TypeToID::Velocity);
                auto &Rb = Engine.getComponent<Rigidbody>(entityID, Components::TypeToID::Rigidbody);
                float deltaTime = Engine.getDeltaTime();

                Pos.x += Vel.Vx * deltaTime;
                Pos.y += Vel.Vy * deltaTime;
                Pos.z += Vel.Vz * deltaTime;
                
                if (Rb.subjectToGravity)
                    Pos.y += gravity * deltaTime;
            }
        };
        ~Movement() {

        };

    protected:
    private:
        static constexpr float gravity = -9.81f;
};

#endif /* !MOVEMENT_HPP_ */
