#ifndef MOVEMENT_HPP_
#define MOVEMENT_HPP_

#include "./Systems.hpp"
#include "../Core/EntityManager.hpp"

extern EntityManager Engine;

class Movement : public ISystem {
    public:
        Movement() {
            this->required.push_back("Position");
            this->required.push_back("Velocity");
        };
        void update() {
            for (auto it = this->entityList.begin(); it != this->entityList.end(); ++it) {
                auto &Pos = Engine.getComponent<Position>((*it), "Position");
                auto &Vel = Engine.getComponent<Velocity>((*it), "Velocity");
                auto &Rb = Engine.getComponent<Rigidbody>((*it), "Rigidbody");
                float deltaTime = Engine.getDeltaTime();

                Pos.x += Vel.Vx * deltaTime;
                Pos.y += Vel.Vy * deltaTime;
                Pos.z += Vel.Vz * deltaTime;
                
                if (Rb.tag != "Crashed" && Rb.subjectToGravity) {
                    Pos.y += gravity * deltaTime;
                }
            }
        };
        ~Movement() {

        };

    protected:
    private:
        const float gravity = -9.81f;
};

#endif /* !MOVEMENT_HPP_ */
